#include <vector>
#include <math.h>
#include "DebugPrint.h"
#include "Point2D.h"
#include "BlockAllocator.h"
#include "FixedSizeAllocator.h"
#include "FSAManager.h"
#include "MemoryOperator.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // _DEBUG

using namespace std;

namespace Engine
{
	BlockAllocator* FSAManager::inst = BlockAllocator::getInstance();
	FSAManager* FSAManager::instance = FSAManager::create();
	FixedSizeAllocator* FSAManager::fixedList[NUM_FSA];

	FSAManager::FSAManager()
	{
		inst = BlockAllocator::getInstance();
		// BlockAllocator HAS TO be created before FSAManager.
	}

	FSAManager::~FSAManager()
	{
		//destroy();
	}

	FSAManager* FSAManager::create()
	{
		if(instance == NULL)
			instance = new (false) FSAManager();
		return instance;
	}

	FSAManager* FSAManager::getInstance()
	{
		return instance;
	}

	void FSAManager::destroy()
	{
		if (!isListEmpty(fixedList, numFSA))
		{
			DEBUG_LOG("Warning: FSA list is not empty.\n");
			clearList(fixedList, numFSA);
		}
		inst->free(instance);
		instance = NULL;
	}

	void FSAManager::createFSA()
	{
		if (!isListEmpty(fixedList, numFSA))
			DEBUG_LOG("Warning: Invalid FSA list. Creation terminated.\n");
		else
		{
			for (size_t i = 0; i < numFSA; i++)
			{
				fixedList[i] = new (false) FixedSizeAllocator(smallestSize * multiplier[i], numBlock, inst);
			}
		}
	}

	bool FSAManager::isListEmpty(FixedSizeAllocator* list[], const size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			if (list[i] != NULL)
			{
				return false;
				break;
			}
		}
		return true;
	}

	void FSAManager::clearList(FixedSizeAllocator* list[], const size_t length)
	{
		for (size_t i = 0; i < length; i++)
		{
			if (list[i] != NULL)
			{
				list[i]->destroy();
				list[i] = NULL;
			}
		}
	}

	FixedSizeAllocator* FSAManager::findFixedSizeAllocator(size_t size)
	{
		if (size <= 0)
		{
			DEBUG_LOG("Warning: Invalid allocation size.\n");
			return NULL;
		}
		else
		{
			for (size_t i = 0; i < numFSA; i++)
			{
				if (size <= fixedList[i]->getBlockSize())
				{
					return fixedList[i];
					break;
				}
			}
			DEBUG_LOG("Appropriate size FSA not found. Use Block Allocator instead.\n");
			return NULL;
		}
	}

	FixedSizeAllocator** FSAManager::getList()
	{
		return fixedList;
	}
}