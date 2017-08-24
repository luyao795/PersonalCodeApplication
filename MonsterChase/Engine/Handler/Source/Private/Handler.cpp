#include <Windows.h>
#include <assert.h>
#include <conio.h>
#include <malloc.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <vector>
#include <algorithm>
#include "BlockAllocator.h"
#include "MemoryOperator.h"
#include "FSAManager.h"
#include "Handler.h"
#include "GLib.h"

using namespace std;

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // _DEBUG

namespace Engine
{
	void StartEngine()
	{
		allocator = BlockAllocator::create(8192, 128);

		manager = FSAManager::create();
		manager->createFSA();
	}

	void CloseEngine()
	{
		manager->destroy();
		manager = NULL;

		if (allocator != NULL)
		{
			allocator->destroy();
			allocator = NULL;
		}
	}
}