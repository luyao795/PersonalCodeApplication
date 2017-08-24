#ifndef BITARRAY_H
#define BITARRAY_H

#include <stdint.h>
#include "BlockAllocator.h"

namespace Engine
{
#ifdef _WIN64
#define u_integer uint64_t
#define integer int64_t
#define MAX_DT UINT64_MAX
#define MAX_BYTE UINT8_MAX
#define ScanBit(index, mask) _BitScanForward64(index, mask)
#else
#define u_integer uint32_t
#define integer int32_t
#define MAX_DT UINT32_MAX
#define MAX_BYTE UINT8_MAX
#define ScanBit(index, mask) _BitScanForward(index, mask)
#endif // _WIN64

	class BitArray
	{
	public:
		BitArray(size_t numBits, bool startClear, BlockAllocator* allocator);
		void create(size_t numBits, bool startClear, BlockAllocator* allocator);

		void clearAll();
		void setAll();

		void destroy();

		bool areAllClear() const;
		bool areAllSet() const;

		bool isBitSet(size_t bitIndex) const;
		bool isBitClear(size_t bitIndex) const;

		void setBit(size_t bitIndex);
		void clearBit(size_t bitIndex);

		bool getFirstClearBit(size_t &outBitIndex) const;
		bool getFirstSetBit(size_t &outBitIndex) const;
		u_integer* getBitArray() const;

		u_integer operator[](size_t bitIndex) const;

	private:
		~BitArray();
		static BlockAllocator* inst;
		u_integer shiftOne = 1;
		u_integer shiftZero = 0;

		size_t wholeBytes;
		size_t extraBits;

		u_integer* bits;
		size_t arraySize;
		size_t numBit;
		const size_t byteSize = 8;
	};
}

#endif // !BITARRAY_H
