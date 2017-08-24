#ifndef FSAMANAGER_H
#define FSAMANAGER_H

#include <vector>
#include "FixedSizeAllocator.h"

#define NUM_FSA 4

namespace Engine
{
	class FSAManager
	{
	public:
		FSAManager();	

		static FSAManager* create();
		static FSAManager* getInstance();
		void destroy();

		void createFSA();
		bool isListEmpty(FixedSizeAllocator* list[], const size_t length);
		void clearList(FixedSizeAllocator* list[], const size_t length);
		FixedSizeAllocator* findFixedSizeAllocator(size_t size);
		FixedSizeAllocator** getList();
		
	private:
		~FSAManager();
		static BlockAllocator* inst;
		static const size_t numFSA = 4;
		// Size: 8, 16, 32, 64
		const size_t multiplier[4] = {1, 2, 4, 8};
		const size_t smallestSize = 8;
		const size_t numBlock = 100;
		static FSAManager* instance;
		//static FixedSizeAllocator** list;
		static FixedSizeAllocator* fixedList[NUM_FSA];
	};

}

#endif // !FSAMANAGER_H
