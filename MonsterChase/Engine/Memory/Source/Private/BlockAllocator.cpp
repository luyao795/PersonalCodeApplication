#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "BlockAllocator.h"
#include "MemoryOperator.h"

using namespace std;

namespace Engine
{
	// Note: If the console shows nothing, go back to Visual Studio without quitting console
	// and you should be able to see a loading dll window. After loading the correct content
	// should show up on console. If not, quit and run again.
	// After first time of loading DLLs in a certain configuration, you won't need to load
	// them under the same configuration again unless you changed something.
	void* BlockAllocator::initialMemory = NULL;
	void* BlockAllocator::freeMemory = NULL;
	void* BlockAllocator::endMemory = NULL;

	BlockDescriptor* BlockAllocator::unusedDescriptor = NULL;
	BlockDescriptor* BlockAllocator::assignedDescriptor = NULL;
	BlockDescriptor* BlockAllocator::outstandingDescriptor = NULL;

	BlockAllocator* BlockAllocator::instance = NULL;

	BlockAllocator::BlockAllocator()
	{
		initialize(defaultSize, defaultNumDes);
	}

	BlockAllocator::BlockAllocator(const size_t memorySize, const unsigned int numDescriptors)
	{
		initialize(memorySize, numDescriptors);
	}

	BlockAllocator::~BlockAllocator()
	{
		//destroy();
	}

	BlockAllocator* BlockAllocator::create(const size_t memorySize, const unsigned int numDescriptors)
	{
		if (instance == NULL)
		{
			// If total memory size is smaller than or equal to zero, return NULL
			if (memorySize <= 0 || numDescriptors <= 0)
				return NULL;
			else
			{
				instance = new (true) BlockAllocator(memorySize, numDescriptors);
			}
		}
		return instance;
	}

	void BlockAllocator::destroy()
	{
		_aligned_free(initialMemory);
		freeMemory = NULL;
		endMemory = NULL;
		initialMemory = NULL;
		operator delete(instance, true);
		instance = NULL;
	}

	void* BlockAllocator::allocate(const size_t size)
	{
		size_t additionalSize;
#ifdef _DEBUG
		additionalSize = 12;
#else
		additionalSize = 0;
#endif // _DEBUG
		// check if request size is valid for allocation
		if (size + additionalSize > getTotalFreeMemory() || size + additionalSize > getLargestFreeBlock())
		{
			fprintf_s(stderr, "Error: Insufficient memory capacity.\n");
			return NULL;
		}
		else
		{
			void* returnToUser;
			// Index of previous pointer
			size_t prevIndex = 0;
			// Sort free descriptor list
			selectionSortLinkedList(assignedDescriptor);
			// Temp pointer to keep track of the current element
			BlockDescriptor* temp = assignedDescriptor;
			// Temp pointer to record the previous pointer of the first qualified one
			BlockDescriptor* prevTemp = assignedDescriptor;
			// Check next element if the current one has smaller size
			while (temp->blockSize < size + additionalSize)
			{
				// Move to next
				temp = temp->next;
				// Increase previous index
				prevIndex++;
			}

			// Decrease previous index by 1
			prevIndex--;

			// Point previous temp to correct address
			for (size_t i = 1; i < prevIndex + 1; i++)
			{
				prevTemp = prevTemp->next;
			}
			// Give the user the entire memory block
			if (temp->blockSize < size + additionalSize + minSize)
			{
				// Shift guard band alignment pointer to end of this block (that contains the part that will return back to the user)
				uintptr_t GBAPointer = reinterpret_cast<uintptr_t>(temp->blockBase) + temp->blockSize;

				// Shift guard band alignment pointer back by the size of right hand guard band as well as user requested size 
				// So that it points to the address that will return to the user if the alignment fits already
				GBAPointer -= (guardband + size);

				// Pointer points to head of left guard band (if no alignment shift needed)
				char* leftGuardBand = reinterpret_cast<char*>(GBAPointer) - guardband;
				char* rightGuardBand = reinterpret_cast<char*>(GBAPointer) + size;

				// The amount of space the pointer needs to shift to fit the 4 byte alignment
				size_t alignDistance = GBAPointer % 4;

				/*********************************************************************************************************************/
				/** We do not have to check whether the left side of left guard band will go beyond the block base address since we **/
				/** have added 12 more bytes for requested size (8 for guard band on both sides and 4 for 4 byte alignment shift).  **/
				/** Therefore, it won't exceed range anyway.                                                                        **/
				/*********************************************************************************************************************/

				// If it's on alignment, write guard band on both sides of the block that user requested
				if (alignDistance == 0)
				{
					writeGuardBand(leftGuardBand, rightGuardBand);
					returnToUser = leftGuardBand + guardband;
				}

				// Otherwise, shift guard band as well as user requested space by the amount of alignment distance
				else
				{
					leftGuardBand -= alignDistance;
					rightGuardBand -= alignDistance;
					writeGuardBand(leftGuardBand, rightGuardBand);
					returnToUser = leftGuardBand + guardband;
				}

				// If it is the head of free list
				if (temp == prevTemp)
				{
					// Increment head by 1
					assignedDescriptor = temp->next;
				}
				prevTemp->next = temp->next;
				temp->next = outstandingDescriptor;
				outstandingDescriptor = temp;
				numDesOutstanding++;
			}
			// Cut the block in half and give them the first (or second) half
			else
			{
				if (numDesUnused == 0)
				{
					fprintf_s(stderr, "Error: Insufficient number of descriptors.\n");
					returnToUser = NULL;
				}
				else
				{
					// Temp cut descriptor that will return to user its block base
					BlockDescriptor* tempCut = unusedDescriptor;
					// Update unused block descriptor
					unusedDescriptor = unusedDescriptor->next;
					// Update data for temp cut and outstanding list head
					tempCut->next = outstandingDescriptor;
					outstandingDescriptor = tempCut;

					// Shift guard band alignment pointer to end of this block (that contains the part that will return back to the user)
					uintptr_t GBAPointer = reinterpret_cast<uintptr_t>(temp->blockBase) + temp->blockSize;

					// Shift guard band alignment pointer back by the size of right hand guard band aswell as user requested size 
					// So that it points to the address that will return to the user if the alignment fits already
					GBAPointer -= (guardband + size);

					// The amount of space the pointer needs to shift to fit the 4 byte alignment
					size_t alignDistance = GBAPointer % 4;

					// Pointer points to head of left guard band (if no alignment shift needed)
					char* leftGuardBand = reinterpret_cast<char*>(GBAPointer) - guardband;
					char* rightGuardBand = reinterpret_cast<char*>(GBAPointer) + size;

					// If it's on alignment, cut the exact size and return the pointer to the user, reduce the size of first half of the block
					if (alignDistance == 0)
					{
						writeGuardBand(leftGuardBand, rightGuardBand);
					}
					// If it's not on alignment, figure out how many extra bytes are needed for shifting and cut with that many extra bytes
					// And reduce the size of first half of the block
					else
					{
						leftGuardBand -= alignDistance;
						rightGuardBand -= alignDistance;
						writeGuardBand(leftGuardBand, rightGuardBand);
					}

					// Update temp block descriptor that still stays in free descriptor list but got size shrinked
					tempCut->blockSize = size + 2 * guardband + alignDistance;
					tempCut->blockBase = reinterpret_cast<char*>(temp->blockBase) + temp->blockSize - size - 2 * guardband - alignDistance;
					temp->blockSize -= (size + 2 * guardband + alignDistance);
					numDesUnused--;
					returnToUser = reinterpret_cast<char*>(tempCut->blockBase) + guardband;
					numDesOutstanding++;
				}
			}
			return returnToUser;

			/*
			BD* new_outstanding_bd = unusedDescriptor;		// save head of unused list into new bd
			unusedDescriptor = unusedDescriptor->next;		// move head of unused list
			new_outstanding_bd->next = NULL;				// remove new bd from unused list

			// initialize new_outstanding_bd

			new_outstanding_bd->next = outstandingDescriptor;			// new_bd points to the current head of the outstanding list
			outstandingDescriptor = new_outstanding_bd;					// move head of the outstanding list to point to new_bd
			*/
		}
	}

	bool BlockAllocator::free(const void* pointer)
	{
		// If it's not a head of outstanding memory, return false
		if (!isAllocated(pointer))
			return false;
		else
		{
			// Temp pointer that checks which descriptor describes the pointer user offered
			BlockDescriptor* temp = outstandingDescriptor;
			// Temp descriptor that refers to the previous descriptor of temp
			BlockDescriptor* tempPrev = outstandingDescriptor;
			// Index for the previous descriptor
			size_t index = 0;
			// If the outstanding descriptor list is not empty
			while (temp != NULL)
			{
				// If the current one is the one that describes the pointer that user offered
				if (temp->blockBase <= pointer && pointer < reinterpret_cast<char*>(temp->blockBase) + temp->blockSize)
				{
					// Set tempPrev to the previous one of temp
					for (size_t i = 1; i < index; i++)
					{
						tempPrev = tempPrev->next;
					}
					if (tempPrev->next == NULL)
					{
						temp->next = assignedDescriptor;
						assignedDescriptor = temp;
						outstandingDescriptor = NULL;
					}
					else
					{
						if (tempPrev == outstandingDescriptor && tempPrev == temp)
						{
							outstandingDescriptor = temp->next;
						}
						else
						{
							tempPrev->next = temp->next;
						}
						temp->next = assignedDescriptor;
						assignedDescriptor = temp;
					}
					numDesOutstanding--;
					return true;
					break;
				}
				index++;
				temp = temp->next;
			}
			return false;
		}
	}

	void BlockAllocator::collect()
	{
		sortBlockListByAddress(assignedDescriptor);
		// Temp pointer used to keep track of current address that we are comparing
		BlockDescriptor* temp = assignedDescriptor;
		// Temp pointer that points to the next address we need to check
		void* tempBase;
		// Temp pointer that traverses through the entire free descriptor list each time temp get incremented
		BlockDescriptor* tempTraverse = assignedDescriptor->next;
		// Temp pointer that points to the previous one of the one that we are merging
		BlockDescriptor* tempPrev = NULL;
		// If there are at least 2 descriptors in outstanding list
		while (temp != NULL)
		{
			// Temp pointer that we need to check for adjacency
			tempBase = reinterpret_cast<char*>(temp->blockBase) + temp->blockSize;
			// If the traversing is not complete
			while (tempTraverse != NULL)
			{
				// If we find the adjacent one
				if (tempBase == tempTraverse->blockBase)
				{
					if (tempPrev != NULL)
					{
						tempPrev->next = tempTraverse->next;
						temp->blockSize += tempTraverse->blockSize;
						// Reset values for block descriptors that are no longer in use
						tempTraverse->blockSize = 0;
						tempTraverse->blockBase = NULL;
						tempTraverse->next = unusedDescriptor;
						unusedDescriptor = tempTraverse;
						tempTraverse = tempPrev->next;
						tempBase = reinterpret_cast<char*>(temp->blockBase) + temp->blockSize;
						numDesUnused++;
						continue;
					}
					else
					{
						temp->blockSize += tempTraverse->blockSize;
						if (temp->next == NULL)
						{
							assignedDescriptor = tempTraverse->next;
							// Reset values for block descriptors that are no longer in use
							tempTraverse->blockSize = 0;
							tempTraverse->blockBase = NULL;
							tempTraverse->next = unusedDescriptor;
							unusedDescriptor = tempTraverse;
							tempTraverse = assignedDescriptor;
						}
						else
						{
							temp->next = tempTraverse->next;
							// Reset values for block descriptors that are no longer in use
							tempTraverse->blockSize = 0;
							tempTraverse->blockBase = NULL;
							tempTraverse->next = unusedDescriptor;
							unusedDescriptor = tempTraverse;
							tempTraverse = temp->next;
						}
						numDesUnused++;
						continue;
					}
				}
				tempPrev = tempTraverse;
				tempTraverse = tempTraverse->next;
			}
			tempTraverse = assignedDescriptor;
			temp = temp->next;
			tempPrev = NULL;
		}
	}

	bool BlockAllocator::contains(const void* pointer) const
	{
		return (pointer >= initialMemory && pointer < endMemory);
	}

	bool BlockAllocator::isAllocated(const void* pointer) const
	{
		BlockDescriptor* temp = outstandingDescriptor;
		if (temp == NULL)
			return false;
		else
		{
			while (temp != NULL)
			{
				if (pointer >= temp->blockBase && pointer < reinterpret_cast<char*>(temp->blockBase) + temp->blockSize)
				{
					return true;
				}
				temp = temp->next;
			}
			return false;
		}
	}

	size_t BlockAllocator::getLargestFreeBlock() const
	{
		size_t largest = 0;
		BlockDescriptor* temp = assignedDescriptor;
		while (temp != NULL)
		{
			if (largest < temp->blockSize)
			{
				largest = temp->blockSize;
			}
			temp = temp->next;
		}
		return largest;
	}

	size_t BlockAllocator::getTotalFreeMemory() const
	{
		size_t freeSize = 0;
		BlockDescriptor* temp = assignedDescriptor;
		while (temp != NULL)
		{
			freeSize += temp->blockSize;
			temp = temp->next;
		}
		return freeSize;
	}

	void BlockAllocator::initialize(const size_t memorySize, const unsigned int numDescriptors)
	{
		size_t numDes = numDescriptors;
		// Set block of memory initially
		initialMemory = reinterpret_cast<char*>(_aligned_malloc(memorySize, alignment));

		// Free memory starts with the beginning of the memory block
		freeMemory = reinterpret_cast<char*>(initialMemory);

		// End of memory that got allocated by aligned malloc
		endMemory = reinterpret_cast<char*>(initialMemory) + memorySize;

		// Free descriptor should be placed at the end of the memory block
		char* descriptorPool = (reinterpret_cast<char*>(initialMemory) + memorySize - numDescriptors * sizeof(BlockDescriptor));

		// Initialize unused block descriptor pool
		for (size_t i = 0; i < numDes; i++)
		{
			// Create a new temp descriptor
			BlockDescriptor* newDescriptor = reinterpret_cast<BlockDescriptor*>(descriptorPool) + i;
			// Set its initial value to NULL/0
			newDescriptor->blockSize = 0;
			newDescriptor->blockBase = NULL;
#ifdef _DEBUG
			newDescriptor->ID = i;
#endif // _DEBUG
			// The next item to the latest new descriptor should be unused descriptor
			newDescriptor->next = unusedDescriptor;
			// Move head of unused descriptor to the latest temp descriptor
			unusedDescriptor = newDescriptor;
		}

		// Unassigned descriptor head should be the same as unused descriptor head before shifting
		assignedDescriptor = unusedDescriptor;

		// Shift head of unused descriptor by 1 unit
		unusedDescriptor = unusedDescriptor->next;

		// Initially there is only one unassigned descriptor which is the big chunk of memory
		assignedDescriptor->next = NULL;
		assignedDescriptor->blockBase = freeMemory;
		assignedDescriptor->blockSize = memorySize - (numDescriptors * sizeof(BlockDescriptor));
		// One descriptor is used for describing the entire big chunk of allocated memory
		numDesUnused = numDescriptors - 1;
		numDesOutstanding = 0;
	}

	// Function that will be used to sort free descriptor list
	void BlockAllocator::selectionSortLinkedList(BlockDescriptor* list)
	{
		/*********************************************************************/
		/** We know for sure that the list would contain at least 1 element **/
		/*********************************************************************/

		// Base element in the list that will be swaped with the element with minimal size
		BlockDescriptor* base = list;
		// Comparator element that will always point to next of base
		BlockDescriptor* comp = base->next;
		// Minimum block size of the remaining unsorted list
		size_t min = base->blockSize;
		// Index of base
		size_t baseIndex = 0;
		// Index of the element with minimum size in unsorted list
		size_t minIndex = 0;

		// If we have not sorted the entire list
		while (comp != NULL)
		{
			size_t curIndex = baseIndex + 1;
			// Actual element that gets compared (and swap) with base
			BlockDescriptor* iter = comp;
			// If we have not compared the final two elements
			while (iter != NULL)
			{
				// Reset minimum size to base
				// No need as we have reset it after the while loop
				//min = base->blockSize;

				// Update minimum size and index if find any
				if (iter->blockSize < min)
				{
					minIndex = curIndex;
					min = iter->blockSize;
				}
				// Iterate to next element of list
				iter = iter->next;
				curIndex++;
			}

			// Reset iter to comp to begin swap
			iter = base;
			// Move iter to minimum element (for swapping)
			for (size_t i = baseIndex; i < minIndex; i++)
			{
				iter = iter->next;
			}
			// Swap base and minimum
			swapDescriptors(base, iter);

			// After each loop of search and swap, set and reset:
			// Increment base and comp by 1
			base = base->next;
			comp = comp->next;
			// Reset minimum size to size of base
			min = base->blockSize;
			// Increment index for base by 1
			baseIndex++;
			// Reset minimum index to base
			minIndex = baseIndex;
		}
	}

	void BlockAllocator::swapDescriptors(BlockDescriptor* first, BlockDescriptor* second)
	{
		void* tempBase = first->blockBase;
		size_t tempSize = first->blockSize;

		first->blockBase = second->blockBase;
		first->blockSize = second->blockSize;

		second->blockBase = tempBase;
		second->blockSize = tempSize;

#ifdef _DEBUG
		size_t tempID = first->ID;
		first->ID = second->ID;
		second->ID = tempID;
#endif // _DEBUG
	}

	void BlockAllocator::sortBlockListByAddress(BlockDescriptor* const list)
	{
		// start pointer
		BlockDescriptor* startPointer = list;
		// compare pointer
		BlockDescriptor* compPointer = startPointer->next;
		// address of memory block with smallest address
		void* minBlock;
		// indexes to keep track of the address of smallest block
		size_t currentIndex = 0;
		size_t minIndex = 0;
		size_t startIndex = 0;

		// check to make sure that next block descriptor is not NULL
		while (startPointer->next != NULL)
		{
			// block descriptor that traverse the list
			BlockDescriptor* traverse = compPointer;
			// compare current to next
			currentIndex = startIndex + 1;
			// store current minimum block address
			minBlock = startPointer->blockBase;
			// check each element in the list
			while (traverse != NULL)
			{
				// update smallest block address
				if (minBlock > traverse->blockBase)
				{
					minIndex = currentIndex;
					minBlock = traverse->blockBase;
				}
				// keep checking next element in the list
				traverse = traverse->next;
				currentIndex++;
			}
			// reset traverse address to go through the list again
			traverse = startPointer;
			for (size_t i = startIndex; i < minIndex; i++)
			{
				traverse = traverse->next;
			}
			// swap block descriptors
			swapDescriptors(traverse, startPointer);
			// update pointer and indexes
			startPointer = startPointer->next;
			startIndex++;
			compPointer = compPointer->next;
			traverse = compPointer;
			minBlock = startPointer->blockBase;
			minIndex = startIndex;
		}
	}

	// write guard band with "XXXX" on each side of memory
	void BlockAllocator::writeGuardBand(char* leftStart, char* rightStart)
	{
		for (size_t i = 0; i < guardband; i++)
		{
			leftStart[0] = 88;
			rightStart[0] = 88;
			leftStart++;
			rightStart++;
		}
	}

	void BlockAllocator::PrintDescriptorID()
	{
#ifdef _DEBUG
		printf_s("Free Descriptor List:\n");
		BlockDescriptor* tempAssigned = assignedDescriptor;
		while (tempAssigned != NULL)
		{
			printf_s("ID: %zu, Size: %zu\n", tempAssigned->ID, tempAssigned->blockSize);
			tempAssigned = tempAssigned->next;
		}
		printf_s("\n");
		printf_s("Unused Descriptor List:\n");
		BlockDescriptor* tempUnused = unusedDescriptor;
		while (tempUnused != NULL)
		{
			printf_s("ID: %zu, Size: %zu\n", tempUnused->ID, tempUnused->blockSize);
			tempUnused = tempUnused->next;
		}
		printf_s("\n");
		printf_s("Outstanding Descriptor List:\n");
		BlockDescriptor* tempOutstanding = outstandingDescriptor;
		while (tempOutstanding != NULL)
		{
			printf_s("ID: %zu, Size: %zu\n", tempOutstanding->ID, tempOutstanding->blockSize);
			tempOutstanding = tempOutstanding->next;
		}
		printf_s("\n");
		printf_s("Number of Outstanding Descriptors: %d\n", numDesOutstanding);
		printf_s("Number of Unused Descriptors: %d\n", numDesUnused);
#endif // _DEBUG
	}

}