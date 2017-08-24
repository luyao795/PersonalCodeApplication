#ifndef FIXEDSIZEALLOCATOR_H
#define FIXEDSIZEALLOCATOR_H

#include "BitArray.h"

namespace Engine
{
	class FixedSizeAllocator
	{
	public:
		FixedSizeAllocator(const size_t size, const size_t numBlocks, BlockAllocator* blockAllocator);

		void destroy();

		void* allocate(size_t size);
		void free(void* pointer);
		bool isInRange(void* pointer, const void* left, const void* right);
		size_t getBlockIndex(void* pointer);

		size_t getBlockSize() const;
		size_t getBlockNumber() const;
		void* getBlockStart() const;
		void* getBlockOver() const;
		BitArray* getBitArray();

	private:
		~FixedSizeAllocator();
		BitArray* bitArray;
		size_t blockSize;
		size_t numBlock;
		static BlockAllocator* allocator;
		void* blockStart;
	};
}

#endif // !FIXEDSIZEALLOCATOR_H
