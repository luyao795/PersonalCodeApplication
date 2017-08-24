#include <stdint.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>
#include "StringPool.h"
#include "BlockAllocator.h"
#include "DebugPrint.h"

#ifdef _DEBUG
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // _DEBUG

using namespace std;

namespace Engine
{
	StringPool* StringPool::instance = NULL;

	StringPool * StringPool::create(size_t bytesInPool)
	{
		static BlockAllocator* allocator = BlockAllocator::getInstance();
		uint8_t * startMemory;
		if (instance == NULL)
		{
			if (allocator != NULL)
			{
				startMemory = reinterpret_cast<uint8_t*>(allocator->allocate(bytesInPool));
				instance = new StringPool(startMemory, bytesInPool);
			}
			else
			{
				ASSERT("Warning: Block Allocator not initialized!\n", allocator != NULL);
			}
		}
		return instance;
	}

	StringPool::~StringPool()
	{
		static BlockAllocator* allocator = BlockAllocator::getInstance();
		ASSERT("Warning: Block Allocator not intialized!\n", allocator != NULL);
		allocator->free(startPool);
		startPool = NULL;
		endPool = NULL;
		endString = NULL;
	}

	const char * StringPool::add(const char * string)
	{
		const char * findResult = find(string);
		if (findResult)
			return findResult;
		else
		{
			const char * result = reinterpret_cast<const char *>(endString);
			size_t length = strlen(string);
			addStringInfo(string);
			result = reinterpret_cast<const char *>(reinterpret_cast<const size_t *>(result) + 1);
			return result;
		}
	}

	const char * StringPool::find(const char * string)
	{
		if (startPool == endString)
			return NULL;
		else
		{
			size_t strlength = strlen(string);
			char * traversalString = reinterpret_cast<char *>(startPool);
			size_t * traversalSize = reinterpret_cast<size_t *>(startPool);
			while (traversalSize != reinterpret_cast<size_t *>(endString))
			{
				size_t numJumpOver = *traversalSize;
				traversalSize++;
				traversalString = reinterpret_cast<char *>(traversalSize);
				if (numJumpOver == strlength)
				{
					if (strcmp(string, traversalString) == 0)
						return traversalString;
					else
					{
						traversalString = traversalString + numJumpOver + 1;
						traversalSize = reinterpret_cast<size_t *>(traversalString);
					}
				}
				else
				{
					traversalString = traversalString + numJumpOver + 1;
					traversalSize = reinterpret_cast<size_t *>(traversalString);
				}
			}
			return NULL;
		}
	}

	void StringPool::addStringInfo(const char * string)
	{
		size_t size = strlen(string);
		size_t * sizePos = reinterpret_cast<size_t *>(endString);

		size_t * boundAfterSize = sizePos + 1;
		uint8_t * boundCheck = reinterpret_cast<uint8_t *>(reinterpret_cast<char *>(boundAfterSize) + size + 1);

		ASSERT("Warning: Writing out of bounds for String Pool!\n", boundCheck <= endPool);

		// Jumping over NUL terminator so that it will not be overwritten by size of next string.
		//sizePos = reinterpret_cast<size_t *>(reinterpret_cast<char *>(endString) + 1);

		*sizePos = size;
		sizePos = sizePos + 1;
		endString = reinterpret_cast<uint8_t *>(sizePos);
		strcpy_s(reinterpret_cast<char *>(sizePos), size + 1, string);
		endString = reinterpret_cast<uint8_t *>(reinterpret_cast<char *>(endString) + size + 1);
	}

	StringPool * StringPool::getInstance()
	{
		return instance;
	}

	StringPool::StringPool(uint8_t * pool, size_t poolSize)
	{
		if (poolSize > 0)
		{
			startPool = pool;
			size = poolSize;
			endString = startPool;
			endPool = startPool + poolSize;
		}
	}
}
