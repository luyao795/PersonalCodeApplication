#include <stdio.h>
#include <malloc.h>
#include "DebugPrint.h"
#include "MemoryOperator.h"
#include "BlockAllocator.h"
#include "FSAManager.h"
#include "FixedSizeAllocator.h"
#include "Point2D.h"

#define ALLOCATE_SIZE 1024
#define ALIGNMENT 4

#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // _DEBUG

using namespace std;
using namespace Engine;

void* operator new(size_t size)
{
	static BlockAllocator* inst = BlockAllocator::getInstance();
	if (inst == NULL)
		inst = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator* fsa = instance->findFixedSizeAllocator(size);
	bool areFull = (fsa) ? fsa->getBitArray()->areAllClear() : true;
	DEBUG_LOG("Calling new(size_t)\nSize: %zu", size);
	return (fsa && !areFull) ? fsa->allocate(size) : inst->allocate(size);
}

// (true) for using system allocation, (false) for using custom allocation.
void* operator new(size_t size, bool allocation)
{
	if (allocation)
	{
		DEBUG_LOG("Calling new(size_t, true)\nSize: %zu", size);
		return _aligned_malloc(size, ALIGNMENT);
	}
	else
	{
		DEBUG_LOG("Calling new(size_t, false)\nSize: %zu", size);
		static BlockAllocator* inst = BlockAllocator::getInstance();
		if (inst == NULL)
			inst = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
		return inst->allocate(size);
	}
}

void* operator new(size_t size, const char* file, const char* func, const unsigned int line)
{
	static BlockAllocator* inst = BlockAllocator::getInstance();
	if (inst == NULL)
		inst = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator* fsa = instance->findFixedSizeAllocator(size);
	bool areFull = (fsa) ? fsa->getBitArray()->areAllClear() : true;
	printf_s("Calling new(size_t, const char*, const char*, const unsigned int)\nSize: %zu\nFile: %s\nFunc: %s\nLine: %d\n\n", size, file, func, line);
	return (fsa && !areFull) ? fsa->allocate(size) : inst->allocate(size);
}

void* operator new[](size_t size)
{
	static BlockAllocator* inst = BlockAllocator::getInstance();
	if (inst == NULL)
		inst = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator* fsa = instance->findFixedSizeAllocator(size);
	bool areFull = (fsa) ? fsa->getBitArray()->areAllClear() : true;
	DEBUG_LOG("Calling new[](size_t)\nSize: %zu", size);
	return (fsa && !areFull) ? fsa->allocate(size) : inst->allocate(size);
}

void * operator new[](size_t size, bool allocation)
{
	if (allocation)
	{
		DEBUG_LOG("Calling new[](size_t, true)\nSize: %zu", size);
		return _aligned_malloc(size, ALIGNMENT);
	}
	else
	{
		DEBUG_LOG("Calling new[](size_t, false)\nSize: %zu", size);
		static BlockAllocator* inst = BlockAllocator::getInstance();
		if (inst == NULL)
			inst = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
		return inst->allocate(size);
	}
}

void operator delete(void* pointer)
{
	bool freeByFSA = false;
	static BlockAllocator* inst = BlockAllocator::getInstance();
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator** list = instance->getList();
	if (inst)
	{
		for (size_t i = 0; i < NUM_FSA; i++)
		{
			if (list[i]->isInRange(pointer, list[i]->getBlockStart(), list[i]->getBlockOver()))
			{
				list[i]->free(pointer);
				freeByFSA = true;
			}
		}
		if(!freeByFSA)
			inst->free(pointer);
		DEBUG_LOG("Calling delete(void*)\nPointer: %p", pointer);
	}
}

void operator delete(void* pointer, bool allocation)
{
	static BlockAllocator* inst = BlockAllocator::getInstance();
	if (inst)
	{
		if (allocation)
		{
			DEBUG_LOG("Calling delete(void*, bool)\nPointer: %p", pointer);
			_aligned_free(pointer);
		}
		else
			operator delete(pointer);
	}
}

void operator delete(void* pointer, const char* file, const char* func, const unsigned int line)
{
	bool freeByFSA = false;
	static BlockAllocator* inst = BlockAllocator::getInstance();
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator** list = instance->getList();
	if (inst)
	{
		for (size_t i = 0; i < NUM_FSA; i++)
		{
			if (list[i]->isInRange(pointer, list[i]->getBlockStart(), list[i]->getBlockOver()))
			{
				list[i]->free(pointer);
				freeByFSA = true;
			}
		}
		if (!freeByFSA)
			inst->free(pointer);
		printf_s("Calling delete(void*, const char*, const char*, const unsigned int)\nPointer: %p\nFile: %s\nFunc: %s\nLine: %d\n\n", pointer, file, func, line);
	}
}

void operator delete[](void* pointer)
{
	bool freeByFSA = false;
	static BlockAllocator* inst = BlockAllocator::getInstance();
	static FSAManager* instance = instance ? instance : FSAManager::create();
	FixedSizeAllocator** list = instance->getList();
	if (inst)
	{
		for (size_t i = 0; i < NUM_FSA; i++)
		{
			if (list[i]->isInRange(pointer, list[i]->getBlockStart(), list[i]->getBlockOver()))
			{
				list[i]->free(pointer);
				freeByFSA = true;
			}
		}
		if (!freeByFSA)
			inst->free(pointer);
		DEBUG_LOG("Calling delete[](void*)\nPointer: %p", pointer);
	}
}

void operator delete[](void * pointer, bool allocation)
{
	static BlockAllocator* inst = BlockAllocator::getInstance();
	if (inst)
	{
		if (allocation)
		{
			DEBUG_LOG("Calling delete[](void*, bool)\nPointer: %p", pointer);
			_aligned_free(pointer);
		}
		else
			operator delete[](pointer);
	}
}
