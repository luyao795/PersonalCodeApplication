#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include "BitArray.h"
#include "MemoryOperator.h"
#include "BlockAllocator.h"

using namespace std;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#endif // _DEBUG


namespace Engine
{
	BlockAllocator* BitArray::inst = BlockAllocator::getInstance();

	BitArray::BitArray(size_t numBits, bool startClear, BlockAllocator* allocator)
	{
		create(numBits, startClear, allocator);
	}

	void BitArray::create(size_t numBits, bool startClear, BlockAllocator* allocator)
	{
		inst = allocator;

		numBit = numBits;

		wholeBytes = numBits / (byteSize * sizeof(u_integer));
		extraBits = numBits % (byteSize * sizeof(u_integer));

		arraySize = (extraBits == 0) ? wholeBytes : wholeBytes + 1;
		bits = new (false) u_integer[arraySize];

		memset(bits, startClear ? 0x00 : MAX_BYTE, sizeof(u_integer) * arraySize);
	}

	void BitArray::clearAll()
	{
		memset(bits, 0x00, sizeof(u_integer) * arraySize);
	}

	void BitArray::setAll()
	{
		memset(bits, MAX_BYTE, sizeof(u_integer) * arraySize);
	}

	void BitArray::destroy()
	{
		//inst->free(bits);
		bits = NULL;
	}

	bool BitArray::areAllClear() const
	{
		unsigned long tempIndex;
		if (extraBits == 0)
		{
			for (size_t i = 0; i < arraySize; i++)
			{
				if (ScanBit(&tempIndex, bits[i]))
					return false;
			}
			return true;
		}
		else
		{
			for (size_t i = 0; i < arraySize - 1; i++)
			{
				if (ScanBit(&tempIndex, bits[i]))
					return false;
			}
			for (size_t j = 0; j < extraBits; j++)
			{
				if (!isBitClear(((arraySize - 1) * sizeof(u_integer)) + j))
					return false;
			}
			return true;
		}
	}

	bool BitArray::areAllSet() const
	{
		if (extraBits == 0)
		{
			for (size_t i = 0; i < arraySize; i++)
			{
				if (bits[i] != MAX_DT)
					return false;
			}
			return true;
		}
		else
		{
			for (size_t i = 0; i < arraySize - 1; i++)
			{
				if (bits[i] != MAX_DT)
					return false;
			}
			for (size_t j = 0; j < extraBits; j++)
			{
				if (!isBitSet(((arraySize - 1) * sizeof(u_integer)) + j))
					return false;
			}
			return true;
		}
	}

	bool BitArray::isBitSet(size_t bitIndex) const
	{
		size_t elementIndex = bitIndex / (sizeof(u_integer) * byteSize);
		size_t shiftIndex = bitIndex % (sizeof(u_integer) * byteSize);
		return (((bits[elementIndex]) >> shiftIndex) & shiftOne) ? true : false;
	}

	bool BitArray::isBitClear(size_t bitIndex) const
	{
		size_t elementIndex = bitIndex / (sizeof(u_integer) * byteSize);
		size_t shiftIndex = bitIndex % (sizeof(u_integer) * byteSize);
		return (((bits[elementIndex]) >> shiftIndex) & shiftOne) ? false : true;
	}

	void BitArray::setBit(size_t bitIndex)
	{
		size_t elementIndex = bitIndex / (sizeof(u_integer) * byteSize);
		size_t shiftIndex = bitIndex % (sizeof(u_integer) * byteSize);
		(bits[elementIndex]) |= shiftOne << shiftIndex;
	}

	void BitArray::clearBit(size_t bitIndex)
	{
		size_t elementIndex = bitIndex / (sizeof(u_integer) * byteSize);
		size_t shiftIndex = bitIndex % (sizeof(u_integer) * byteSize);
		(bits[elementIndex]) &= ~(shiftOne << shiftIndex);
	}

	bool BitArray::getFirstClearBit(size_t &outBitIndex) const
	{
		if (extraBits == 0)
		{
			for (size_t i = 0; i < arraySize; i++)
			{
				if (bits[i] != MAX_DT)
				{
					for (size_t j = 0; j < sizeof(u_integer) * byteSize; j++)
					{
						if (isBitClear((i * sizeof(u_integer) * byteSize) + j))
						{
							outBitIndex = (i * sizeof(u_integer) * byteSize) + j;
							return true;
						}
					}
				}
			}
			return false;
		}
		else
		{
			for (size_t i = 0; i < arraySize - 1; i++)
			{
				if (bits[i] != MAX_DT)
				{
					for (size_t j = 0; j < sizeof(u_integer) * byteSize; j++)
					{
						if (isBitClear((i * sizeof(u_integer) * byteSize) + j))
						{
							outBitIndex = (i * sizeof(u_integer) * byteSize) + j;
							return true;
						}
					}
				}
			}
			for (size_t i = 0; i < extraBits; i++)
			{
				if (isBitClear(((arraySize - 1) * sizeof(u_integer) * byteSize) + i))
				{
					outBitIndex = ((arraySize - 1) * sizeof(u_integer) * byteSize) + i;
					return true;
				}
			}
			return false;
		}
	}

	bool BitArray::getFirstSetBit(size_t &outBitIndex) const
	{
		unsigned long index;
		if (extraBits == 0)
		{
			for (size_t i = 0; i < arraySize; i++)
			{
				if (ScanBit(&index, bits[i]))
				{
					outBitIndex = i * sizeof(u_integer) + index;
					return true;
				}
			}
			return false;
		}
		else
		{
			for (size_t i = 0; i < arraySize - 1; i++)
			{
				if (ScanBit(&index, bits[i]))
				{
					outBitIndex = i * sizeof(u_integer) + index;
					return true;
				}
			}
			for (size_t j = 0; j < extraBits; j++)
			{
				if (isBitSet(((arraySize - 1) * sizeof(u_integer)) + j))
				{
					outBitIndex = ((arraySize - 1) * sizeof(u_integer)) + j;
					return true;
				}
			}
			return false;
		}
	}

	u_integer* BitArray::getBitArray() const
	{
		return bits;
	}

	u_integer BitArray::operator[](size_t bitIndex) const
	{
		size_t elementIndex = bitIndex / (sizeof(u_integer) * byteSize);
		size_t shiftIndex = bitIndex % (sizeof(u_integer) * byteSize);
		return ((bits[elementIndex]) >> shiftIndex) & 1;
	}

	BitArray::~BitArray()
	{
		//destroy();
	}
}