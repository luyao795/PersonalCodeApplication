#include <stdint.h>
#include "DebugPrint.h"
#include "BlockAllocator.h"
#include "Point2D.h"
#include "BitArray.h"
#include "FixedSizeAllocator.h"
#include "MemoryOperator.h"

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#define TRACK_NEW (__FILE__, __FUNCTION__, __LINE__)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#define TRACK_NEW
#endif // _DEBUG

using namespace std;

namespace Engine
{
	BlockAllocator* FixedSizeAllocator::allocator = BlockAllocator::getInstance();

	FixedSizeAllocator::FixedSizeAllocator(const size_t size, const size_t numBlocks, BlockAllocator* blockAllocator)
	{
		blockSize = size;
		numBlock = numBlocks;
		allocator = blockAllocator;
		blockStart = blockAllocator->allocate(size * numBlocks);
		bitArray = new (false) BitArray(numBlocks, false, blockAllocator);
	}

	FixedSizeAllocator::~FixedSizeAllocator()
	{
		//destroy();
	}

	void FixedSizeAllocator::destroy()
	{
		size_t firstClear;
		if (bitArray->getFirstClearBit(firstClear))
		{
			DEBUG_LOG("Warning, outstanding allocation detected!\n");
		}
		bitArray->destroy();
		bitArray = NULL;
		allocator->free(blockStart);
	}

	void* FixedSizeAllocator::allocate(size_t size)
	{
		if(size > blockSize)
			return NULL;
		else
		{
			size_t firstAvailable;
			if (bitArray->getFirstSetBit(firstAvailable))
			{
				bitArray->clearBit(firstAvailable);
				return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(blockStart) + (firstAvailable * blockSize));
			}
			else
				return NULL;
		}
	}

	void FixedSizeAllocator::free(void* pointer)
	{
		if (!isInRange(pointer, blockStart, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(blockStart) + blockSize * numBlock)))
			DEBUG_LOG("Pointer not in range. Free using corresponding allocator.\n");
		else
		{
			size_t index = getBlockIndex(pointer);
			if (!bitArray->isBitClear(index))
				DEBUG_LOG("Given pointer is not an outstanding one.\n");
			else
				bitArray->setBit(index);
		}
	}

	bool FixedSizeAllocator::isInRange(void* pointer, const void* left, const void* right)
	{
		return (pointer >= left && pointer < right) ? true : false;
	}

	size_t FixedSizeAllocator::getBlockIndex(void* pointer)
	{
		for (size_t i = 0; i < numBlock; i++)
		{
			if (isInRange(pointer, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(blockStart) + blockSize * i), reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(blockStart) + blockSize * (i + 1))))
			{
				return i;
			}
		}
		DEBUG_LOG("Pointer is out of range.\n");
		return NULL;
	}

	size_t FixedSizeAllocator::getBlockSize() const
	{
		return blockSize;
	}

	size_t FixedSizeAllocator::getBlockNumber() const
	{
		return numBlock;
	}

	void* FixedSizeAllocator::getBlockStart() const
	{
		return blockStart;
	}

	void* FixedSizeAllocator::getBlockOver() const
	{
		return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(blockStart) + blockSize * numBlock);
	}

	BitArray * FixedSizeAllocator::getBitArray()
	{
		return bitArray;
	}
}
