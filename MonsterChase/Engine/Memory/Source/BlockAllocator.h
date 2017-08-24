#ifndef ALLOCATOR_H
#define ALLOCATOR_H

namespace Engine
{
	struct BlockDescriptor
	{
		void* blockBase;
		size_t blockSize;
		BlockDescriptor* next;
#ifdef _DEBUG
		size_t ID;
#endif // _DEBUG
	};

	class BlockAllocator
	{
	public:
		// create a new Block Allocator
		static BlockAllocator* create(const size_t memorySize, const unsigned int numDescriptors);
		// destroy the Block Allocator
		static void destroy();

		inline static BlockAllocator* getInstance();

		// allocate memory with 4 byte alignment and optional guardband (activate in Debug mode)
		void* allocate(const size_t size);

		void selectionSortLinkedList(BlockDescriptor* list);

		void swapDescriptors(BlockDescriptor* first, BlockDescriptor* sencond);

		void sortBlockListByAddress(BlockDescriptor* const list);

		void writeGuardBand(char* leftStart, char* rightStart);

		// free memory
		bool free(const void* pointer);

		// run garbage collection
		void collect();

		// check whether a given pointer is within the allocated memory range
		bool contains(const void* pointer) const;

		// check whether a given pointer is an outstanding allocation
		bool isAllocated(const void* pointer) const;

		size_t getLargestFreeBlock() const;
		size_t getTotalFreeMemory() const;

		void initialize(const size_t memorySize, const unsigned int numDescriptors);

		void PrintDescriptorID();

	private:
		BlockAllocator();
		BlockAllocator(const size_t memorySize, const unsigned int numDescriptors);
		~BlockAllocator();
		static BlockAllocator* instance;

		const size_t minSize = 16;
		const size_t defaultSize = 1024 * 1024;
		const unsigned int defaultNumDes = 2048;
		static const size_t alignment = 4;
#ifdef _DEBUG
		static const size_t guardband = 4;
#else
		static const size_t guardband = 0;
#endif // _DEBUG
		static void* initialMemory;
		static void* freeMemory;
		static void* endMemory;

		// descriptor head that points to nothing
		static BlockDescriptor* unusedDescriptor;
		// descriptor head that points to the beginning of free memory
		static BlockDescriptor* assignedDescriptor;
		// descriptor head that points to the beginning of outstanding memory
		static BlockDescriptor* outstandingDescriptor;

		// number of unused descriptors left
		unsigned int numDesUnused;
		// number of outstanding descriptors left
		unsigned int numDesOutstanding;
	};

}

#include "BlockAllocator.hpp"
#endif // ALLOCATOR_H
