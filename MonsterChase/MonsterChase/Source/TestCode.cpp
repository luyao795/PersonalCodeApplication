//void StringPoolTest()
//{
//	// Unit Test for String Pool
//	//static StringPool* pool = StringPool::create(256 * 256);
//	//const char * doggo1 = pool->find("doggo");
//
//	//assert(doggo1 == nullptr);
//
//	//const char * apple1 = pool->add("apple");
//	//const char * puppy1 = pool->add("pupper");
//
//	//const char * apple2 = pool->add("apple");
//	//const char * puppy2 = pool->add("puppy");
//
//	//const char * doggo2 = pool->find("doggo");
//
//	//assert(doggo2 == nullptr);
//
//	//assert(apple1 == apple2);
//	//assert(puppy1 == puppy2);
//}
//
//
//void SmartWeakPointerTest()
//{
//	// Unit Test
//	//ReferenceCounter* ref = new ReferenceCounter();
//	//SmartPointer<GameObject> sm(new GameObject(), ref);
//	//SmartPointer<GameObject> stupid(sm);
//	//SmartPointer<GameObject> superStupid(move(stupid)); // stupid became NULL after moving it to superStupid
//	//SmartPointer<GameObject> thisisstupid = sm;
//
//	//WeakPointer<GameObject> wk(sm);
//	//WeakPointer<GameObject> wk2(wk);
//	//WeakPointer<GameObject> wk3(move(wk));
//
//	//SmartPointer<GameObject> sth = wk2.AcquireSmart();
//
//	//assert(sth == sm);
//
//	//delete ref;
//	//ref = NULL;
//}
//
//
//void FSABitArrayTest()
//{
//	//	BlockAllocator* pHeapManager = BlockAllocator::create(1024 * 1024, 2048);
//	//
//	//	FSAManager* manager = FSAManager::create();
//	//	manager->createFSA();
//	//
//	//	const size_t 		sizeHeap = 1024 * 1024;
//	//	const unsigned int 	numDescriptors = 2048;
//	//
//	//	// Allocate memory for my test heap.
//	//	//void * pHeapMemory = _aligned_malloc(sizeHeap, 4);
//	//	//assert(pHeapMemory);
//	//
//	//	// Create a heap manager for my test heap.
//	//	//BlockAllocator * pHeapManager = BlockAllocator::create(sizeHeap, numDescriptors);
//	//	assert(pHeapManager);
//	//
//	//	UnitTest(pHeapManager);
//	//	
//	//	manager->destroy();
//	//
//	//	pHeapManager->destroy();
//	//	pHeapManager = NULL;
//	//
//	//	manager = NULL;
//	//
//	//
//	//	//_aligned_free(pHeapMemory);
//	//
//	//	/*
//	//	const size_t bitCount = 1000;
//	//
//	//	BitArray* pMyArray = new BitArray(bitCount, true, allocator);
//	//
//	//	pMyArray->setBit(20);
//	//
//	//	bool b1 = pMyArray->isBitSet(20);
//	//
//	//	printf("\n");
//	//
//	//	size_t firstSetBit = 0;
//	//	size_t firstClearBit = 0;
//	//
//	//	bool foundSetBit = pMyArray->getFirstSetBit(firstSetBit);
//	//	assert(foundSetBit && (firstSetBit == 20));
//	//
//	//	pMyArray->clearBit(20);
//	//	foundSetBit = pMyArray->getFirstSetBit(firstSetBit);
//	//	assert(foundSetBit == false);
//	//
//	//	printf("\n");
//	//
//	//	for (unsigned int i = 0; i < bitCount; i++)
//	//	{
//	//		assert(pMyArray->isBitClear(i) == true);
//	//		assert(pMyArray->isBitSet(i) == false);
//	//
//	//		size_t bit = 0;
//	//
//	//		pMyArray->getFirstClearBit(bit);
//	//		assert(bit == i);
//	//
//	//		pMyArray->setBit(i);
//	//
//	//		assert(pMyArray->isBitClear(i) == false);
//	//		assert(pMyArray->isBitSet(i) == true);
//	//
//	//		bool success = pMyArray->getFirstClearBit(bit);
//	//		assert(((i < (bitCount - 1)) && success && (bit == (i + 1))) || ((i == (bitCount - 1)) && !success));
//	//	}
//	//
//	//	pMyArray->setAll();
//	//	assert(pMyArray->getFirstClearBit(firstClearBit) == false);
//	//
//	//	pMyArray->clearAll();
//	//	assert(pMyArray->getFirstSetBit(firstSetBit) == false);
//	//
//	//	delete pMyArray;
//	//	*/
//}
//
//void BlockAllocatorTest()
//{
//	// NOTE: When put this function back into main file, add parameter "BlockAllocator* pHeapManager" to this function.
//
//	//#ifdef TEST_SINGLE_LARGE_ALLOCATION
//	//	// This is a test I wrote to check to see if using the whole block if it was almost consumed by 
//	//	// an allocation worked. Also helped test my ShowFreeBlocks() and ShowOutstandingAllocations().
//	//{
//	//	ShowFreeBlocks(pHeapManager);
//	//
//	//	size_t largestBeforeAlloc = GetLargestFreeBlock(pHeapManager);
//	//	void * pPtr = alloc(pHeapManager, largestBeforeAlloc - HeapManager::s_MinumumToLeave);
//	//
//	//	if (pPtr)
//	//	{
//	//#ifdef __SHOW_FREE_BLOCKS
//	//		ShowFreeBlocks(pHeapManager);
//	//		printf("\n");
//	//#endif // __SHOW_FREE_BLOCKS
//	//#ifdef __SHOW_ALLOCATIONS
//	//		ShowOutstandingAllocations(pHeapManager);
//	//		printf("\n");
//	//#endif // __SHOW_ALLOCATIONS
//	//
//	//		size_t largestAfterAlloc = GetLargestFreeBlock(pHeapManager);
//	//		free(pHeapManager, pPtr);
//	//
//	//#ifdef __SHOW_FREE_BLOCKS
//	//		ShowFreeBlocks(pHeapManager);
//	//#endif // __SHOW_FREE_BLOCKS
//	//#ifdef __SHOW_ALLOCATIONS
//	//		ShowOutstandingAllocations(pHeapManager);
//	//#endif // __SHOW_ALLOCATIONS
//	//		printf("\n");
//	//
//	//		Collect(pHeapManager);
//	//#ifdef __SHOW_FREE_BLOCKS
//	//		ShowFreeBlocks(pHeapManager);
//	//#endif // __SHOW_FREE_BLOCKS
//	//#ifdef __SHOW_ALLOCATIONS
//	//		ShowOutstandingAllocations(pHeapManager);
//	//#endif // __SHOW_ALLOCATIONS
//	//		printf("\n");
//	//
//	//		size_t largestAfterCollect = GetLargestFreeBlock(pHeapManager);
//	//	}
//	//}
//	//#endif
//	//
//	//	std::vector<void *> AllocatedAddresses;
//	//
//	//	long	numAllocs = 0;
//	//	long	numFrees = 0;
//	//	long	numCollects = 0;
//	//
//	//	bool	done = false;
//	//
//	//	// allocate memory of random sizes up to 1024 bytes from the heap manager
//	//	// until it runs out of memory
//	//	do
//	//	{
//	//		const size_t		maxTestAllocationSize = 1024;
//	//
//	//		size_t			sizeAlloc = 1 + (rand() & (maxTestAllocationSize - 1));
//	//
//	//#ifdef SUPPORT_ALIGNMENT
//	//		const unsigned int	alignments[] = { 4, 8, 16, 32, 64 };
//	//
//	//		unsigned int	index = rand() % (sizeof(alignments) / sizeof(alignments[0]));
//	//
//	//		unsigned int	alignment = alignments[index];
//	//
//	//		void * pPtr = alloc(pHeapManager, sizeAlloc, alignment);
//	//
//	//		assert((reinterpret_cast<uintptr_t>(pPtr) & (alignment - 1)) == 0);
//	//#else
//	//		void * pPtr = pHeapManager->allocate(sizeAlloc);
//	//#endif // SUPPORT_ALIGNMENT
//	//
//	//		if (pPtr == NULL)
//	//		{
//	//			pHeapManager->collect();
//	//
//	//#ifdef SUPPORT_ALIGNMENT
//	//			pPtr = alloc(pHeapManager, sizeAlloc, alignment);
//	//#else
//	//			pPtr = pHeapManager->allocate(sizeAlloc);
//	//#endif // SUPPORT_ALIGNMENT
//	//
//	//			if (pPtr == NULL)
//	//			{
//	//				done = true;
//	//				break;
//	//			}
//	//		}
//	//
//	//		AllocatedAddresses.push_back(pPtr);
//	//		numAllocs++;
//	//
//	//		const unsigned int freeAboutEvery = 10;
//	//		const unsigned int garbageCollectAboutEvery = 40;
//	//
//	//		if (!AllocatedAddresses.empty() && ((rand() % freeAboutEvery) == 0))
//	//		{
//	//			void * pPtr = AllocatedAddresses.back();
//	//			AllocatedAddresses.pop_back();
//	//
//	//			bool success = pHeapManager->free(pPtr);
//	//			assert(success);
//	//
//	//			numFrees++;
//	//		}
//	//
//	//		if ((rand() % garbageCollectAboutEvery) == 0)
//	//		{
//	//			pHeapManager->collect();
//	//
//	//			numCollects++;
//	//		}
//	//
//	//	} while (1);
//	//
//	//#ifdef __SHOW_FREE_BLOCKS
//	//	printf("After exhausting allocations:\n");
//	//	ShowFreeBlocks(pHeapManager);
//	//#endif // __SHOW_FREE_BLOCKS
//	//
//	//#ifdef __SHOW_ALLOCATIONS
//	//	ShowOutstandingAllocations(pHeapManager);
//	//#endif // __SHOW_ALLOCATIONS
//	//	printf("\n");
//	//	pHeapManager->PrintDescriptorID();
//	//
//	//	// now free those blocks in a random order
//	//	if (!AllocatedAddresses.empty())
//	//	{
//	//		// randomize the addresses
//	//		random_shuffle(AllocatedAddresses.begin(), AllocatedAddresses.end());
//	//
//	//		// return them back to the heap manager
//	//		while (!AllocatedAddresses.empty())
//	//		{
//	//			void * pPtr = AllocatedAddresses.back();
//	//			AllocatedAddresses.pop_back();
//	//
//	//			bool success = pHeapManager->contains(pPtr);
//	//			assert(success);
//	//
//	//			success = pHeapManager->isAllocated(pPtr);
//	//			assert(success);
//	//
//	//			success = pHeapManager->free(pPtr);
//	//			assert(success);
//	//		}
//	//
//	//#ifdef __SHOW_FREE_BLOCKS
//	//		printf("After freeing allocations:\n");
//	//		ShowFreeBlocks(pHeapManager);
//	//#endif // __SHOW_FREE_BLOCKS
//	//
//	//#ifdef __SHOW_ALLOCATIONS
//	//		ShowOutstandingAllocations(pHeapManager);
//	//#endif // __SHOW_ALLOCATIONS
//	//
//	//		// do garbage collection
//	//		pHeapManager->collect();
//	//		// our heap should be one single block, all the memory it started with
//	//
//	//#ifdef __SHOW_FREE_BLOCKS
//	//		printf("After garbage collection:\n");
//	//		ShowFreeBlocks(pHeapManager);
//	//#endif // __SHOW_FREE_BLOCKS
//	//
//	//#ifdef __SHOW_ALLOCATIONS
//	//		ShowOutstandingAllocations(pHeapManager);
//	//#endif // __SHOW_ALLOCATIONS
//	//
//	//		pHeapManager->PrintDescriptorID();
//	//		printf("\n");		// do a large test allocation to see if garbage collection worked
//	//		void * pPtr = pHeapManager->allocate(1024 * 1024 / 2);
//	//		assert(pPtr);
//	//
//	//		if (pPtr)
//	//		{
//	//			bool success = pHeapManager->free(pPtr);
//	//			assert(success);
//	//
//	//		}
//	//	}
//	//	pHeapManager->PrintDescriptorID();
//}
//
//void NANTest()
//{
//	////  #ifdef _DEBUG	
//	////	// Here is the CheckNaN unit test.
//	////	
//	////	const float f1 = 1.0f;
//	////	const float f2 = -0.0f;
//	////	const float f3 = 0.0f;
//	////	const float f4 = -1.0f;
//	////	const float f5 = f4 + f1;
//	////	const float f6 = f1 * f2;
//	////
//	////	// Can't check things like 1.0f / 0.0f as the compiler will complain about it.
//	////
//	////	if (!CheckNaN(f1))
//	////		printf_s("f1 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f1 didn't pass CheckNaN test.\n");
//	////
//	////	if (!CheckNaN(f2))
//	////		printf_s("f2 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f2 didn't pass CheckNaN test.\n");
//	////
//	////	if (!CheckNaN(f3))
//	////		printf_s("f3 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f3 didn't pass CheckNaN test.\n");
//	////
//	////	if (!CheckNaN(f4))
//	////		printf_s("f4 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f4 didn't pass CheckNaN test.\n");
//	////
//	////	if (!CheckNaN(f5))
//	////		printf_s("f5 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f5 didn't pass CheckNaN test.\n");
//	////
//	////	if (!CheckNaN(f6))
//	////		printf_s("f6 passed CheckNaN test.\n");
//	////	else
//	////		printf_s("f6 didn't pass CheckNaN test.\n");
//	////
//	////	printf_s("\n");
//	////
//	////#endif // _DEBUG
//}
//
//void FloatTest()
//{
//	////	// Here is the float comparison unit test.
//	////
//	////  #ifdef _DEBUG	
//	////
//	////	const float f7 = 1.0000000001f;
//	////	const float f8 = 1.0000000101f;
//	////	const float f9 = 1.0000010101f;
//	////	const float f0 = 1.0001010101f;
//	////	const float fx = 1.0101010101f;
//	////
//	////	if (AreAboutEqual(f2, f3))
//	////		printf_s("f2 and f3 are equal generally with fixed epsilon comparison.\n");
//	////	else
//	////		printf_s("f2 and f3 are not equal generally with fixed epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f2, f3, 0.00000001f))
//	////		printf_s("f2 and f3 are equal generally with custom epsilon comparison.\n");
//	////	else
//	////		printf_s("f2 and f3 are not equal generally with custom epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f7, f8))
//	////		printf_s("f7 and f8 are equal generally with fixed epsilon comparison.\n");
//	////	else
//	////		printf_s("f7 and f8 are not equal generally with fixed epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f7, f8, 0.00000001f))
//	////		printf_s("f7 and f8 are equal generally with custom epsilon comparison.\n");
//	////	else
//	////		printf_s("f7 and f8 are not equal generally with custom epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f8, f9))
//	////		printf_s("f8 and f9 are equal generally with fixed epsilon comparison.\n");
//	////	else
//	////		printf_s("f8 and f9 are not equal generally with fixed epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f8, f9, 0.00000001f))
//	////		printf_s("f8 and f9 are equal generally with custom epsilon comparison.\n");
//	////	else
//	////		printf_s("f8 and f9 are not equal generally with custom epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f9, f0))
//	////		printf_s("f9 and f0 are equal generally with fixed epsilon comparison.\n");
//	////	else
//	////		printf_s("f9 and f0 are not equal generally with fixed epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f9, f0, 0.00000001f))
//	////		printf_s("f9 and f0 are equal generally with custom epsilon comparison.\n");
//	////	else
//	////		printf_s("f9 and f0 are not equal generally with custom epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f0, fx))
//	////		printf_s("f0 and fx are equal generally with fixed epsilon comparison.\n");
//	////	else
//	////		printf_s("f0 and fx are not equal generally with fixed epsilon comparison.\n");
//	////
//	////	if (AreAboutEqual(f0, fx, 0.00000001f))
//	////		printf_s("f0 and fx are equal generally with custom epsilon comparison.\n");
//	////	else
//	////		printf_s("f0 and fx are not equal generally with custom epsilon comparison.\n");
//	////
//	////	printf_s("\n");
//	////#endif // _DEBUG
//}
//
//void MoveCopyConstructorTest()
//{
//	////	// Side game works as unit test for copy (move) constructors and copy (move) assignment operators.
//	////
//	////	int numMon = 10;
//	////	int regMon = 5;
//	////	Monster sample;
//	////	printf_s("Expected: Calling regular constructor.\n");
//	////	sample.SetName("Sample");
//	////	// testing copy constructor, works fine.
//	////	Monster temp(sample);
//	////	printf_s("Expected: Calling copy constructor.\n");
//	////	printf_s("Expected: Sample; Actual: %s\n", temp.GetName());
//	////	// testing copy assignment operator, works fine.
//	////	Monster temp2;
//	////	temp2 = sample;
//	////	printf_s("Expected: Calling copy assignment operator.\n");
//	////	printf_s("Expected: Sample; Actual: %s\n", temp2.GetName());
//	////
//	////	Monster sample2;
//	////	printf_s("Expected: Calling regular constructor.\n");
//	////	sample2.SetName("MoveSample");
//	////
//	////	// testing move constructor, works fine.
//	////	Monster moveMon(move(sample2));
//	////	printf_s("Expected: Calling move constructor.\n");
//	////	printf_s("Expected: MoveSample; Actual: %s\n", moveMon.GetName());
//	////
//	////	Monster sample3;
//	////	printf_s("Expected: Calling regular constructor.\n");
//	////	sample3.SetName("MoveSampleAssignment");
//	////
//	////	// testing move assignment operator, works fine.
//	////	Monster moveAss;
//	////	moveAss = move(sample3);
//	////	printf_s("Expected: Calling move assignment operator.\n");
//	////	printf_s("Expected: MoveSampleAssignment; Actual: %s\n", moveAss.GetName());
//	////
//	////	// testing copy constructor and move constructor in vector, works fine.
//	////	vector<Monster> mons;
//	////	mons.reserve(numMon);
//	////	for (int i = 0; i < regMon; i++)
//	////	{
//	////		mons.push_back(sample);
//	////		printf_s("Expected: Calling copy constructor.\n");
//	////	}
//	////	for (int i = regMon; i < numMon; i++)
//	////	{
//	////		mons.push_back(move(sample));
//	////		printf_s("Expected: Calling move constructor.\n");
//	////	}
//	////
//	////	mons.clear();
//}
//
//void MainTextGame()
//{
//	////	// Main Game
//	////
//	////	const unsigned int maxMonster = 10;
//	////	const unsigned int minMonster = 4;
//	////	const unsigned int maxGoomba = 5;
//	////	const unsigned int minGoomba = 2;
//	////
//	////	//Monster monsterList[5] = {};
//	////
//	////	Monster *monsterLists[maxMonster];
//	////
//	////	Goomba *goombaLists[maxGoomba];
//	////
//	////	for (int i = 0; i < maxMonster; i++)
//	////	{
//	////		monsterLists[i] = NULL;
//	////	}
//	////
//	////	for (int i = 0; i < maxGoomba; i++)
//	////	{
//	////		goombaLists[i] = NULL;
//	////	}
//	////
//	////	//Player p(0, 0);
//	////
//	////	Player *pp = new TRACK_NEW Player();
//	////
//	////	PlayerController *controller = new PlayerController();
//	////	MonsterController *monController = new MonsterController();
//	////	GoombaController *gooController = new GoombaController();
//	////
//	////	controller->SetGameObject(pp);
//	////	monController->SetFocusObject(pp);
//	////	gooController->SetFocusObject(pp);
//	////
//	////	int numMonster = 0;
//	////	int currentlyAlive = 0;
//	////
//	////	int numGoomba = rand() % 3 + 2;
//	////	int currentlyAliveGoomba = 0;
//	////
//	////	//char *pName = reinterpret_cast<char*>(malloc(sizeof(char) * 20));
//	////
//	////	char *pName = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 100));
//	////
//	////	Sleep(1000);
//	////
//	////	printf_s("Hello, warrior. I've seen you before but I forgot your name, mind telling me again? (Max length 20) ");
//	////	printf_s("\n");
//	////
//	////	scanf_s("%s", pName, 20);
//	////	printf_s("\n");
//	////
//	////	pp->SetName(pName);
//	////
//	////	Sleep(1000);
//	////
//	////	printf_s("That's right! You are %s! Nice to meet you again!\n", pp->GetName());
//	////	printf_s("\n");
//	////
//	////	Sleep(3000);
//	////
//	////	printf_s("There is no time for chitchatting now! We are now in a dangerous dungeon!\n");
//	////	printf_s("\n");
//	////
//	////	Sleep(3000);
//	////
//	////	printf_s("One thing I need to remind you: this dungeon is weird. As long as there are less than 4 monsters in it, it will spawn new monsters, so be careful!\n");
//	////	printf_s("\n");
//	////
//	////	Sleep(3000);
//	////
//	////	printf_s("By the way, how many monsters are there in this dungeon? You just checked the map, so please tell me. ");
//	////	printf_s("\n");
//	////
//	////	scanf_s("%d", &numMonster);
//	////	printf_s("\n");
//	////
//	////	Sleep(1000);
//	////
//	////	// make sure number of monster is in range [4, 10]
//	////	if (numMonster > maxMonster)
//	////	{
//	////		printf_s("Don't lie to me! This dungeon is not that hard! I have checked the walkthrough guide! There must be 10 monsters in this dungeon!\n");
//	////		printf_s("\n");
//	////		numMonster = maxMonster;
//	////	}
//	////
//	////	else if (numMonster < minMonster)
//	////	{
//	////		printf_s("Don't lie to me! This dungeon is not that peaceful! I have checked the walkthrough guide! There must be 4 monsters in this dungeon!\n");
//	////		printf_s("\n");
//	////		numMonster = minMonster;
//	////	}
//	////
//	////	else
//	////	{
//	////		printf_s("Thanks for the information! So there are %d monsters in the dungeon, huh.\n", numMonster);
//	////		printf_s("\n");
//	////	}
//	////	Sleep(3000);
//	////
//	////	printf_s("Well, I need to leave now, one last piece of useful advice: try to escape if you can, no one will look down upon you!\n");
//	////	printf_s("\n");
//	////
//	////	Sleep(3000);
//	////
//	////	printf_s("You entered the dungeon. There are currently %d monsters in this dungeon. Good luck!\n", numMonster);
//	////	printf_s("\n");
//	////
//	////	Sleep(2000);
//	////
//	////	printf_s("Warning! Goomba detected! There are %d Goombas in the dungeon!\n", numGoomba);
//	////	printf_s("\n");
//	////
//	////	Sleep(3000);
//	////
//	////	ASSERT("Invalid number. Abort!", ((numMonster >= 0) && (numMonster <= maxMonster)));
//	////	ASSERT("Invalid number. Abort!", ((numGoomba >= 0) && (numGoomba <= maxGoomba)));
//	////
//	////	// (testing for) activating and setting up names and positions for monster objects
//	////	for (int i = 0; i < numMonster; i++)
//	////	{
//	////		monsterLists[i] = new Monster();
//	////		monController->SetGameObject(monsterLists[i]);
//	////		monController->SetGameObjectPosition();
//	////		//monsterList[i].Activate();
//	////		//char* name = (char *)malloc(sizeof(char) * 12);
//	////		char* name = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 12));
//	////		printf_s("Please enter name for monster %d (Max length 10): ", i + 1);
//	////		printf_s("\n");
//	////		scanf_s("%s", name, 10);
//	////		printf_s("\n");
//	////		//monsterList[i].SetName(name);
//	////		monsterLists[i]->SetName(name);
//	////		Sleep(500);
//	////		printf_s("Roger! The name for monster %d is %s!\n", i + 1, monsterLists[i]->GetName());
//	////		printf_s("Monster %s is currently at [%d, %d] with %d point(s) of health!\n", monsterLists[i]->GetName(), monController->GetGameObject()->GetPosition().GetX(), monController->GetGameObject()->GetPosition().GetY(), monsterLists[i]->GetHealth());
//	////		printf_s("\n");
//	////		Sleep(1000);
//	////	}
//	////
//	////	for (int i = 0; i < numGoomba; i++)
//	////	{
//	////		goombaLists[i] = new Goomba();
//	////		gooController->SetGameObject(goombaLists[i]);
//	////		gooController->SetGameObjectPosition();
//	////		Sleep(500);
//	////		printf_s("Goomba %d is currently at [%d, %d] with %d point(s) of health!\n", i + 1, gooController->GetGameObject()->GetPosition().GetX(), gooController->GetGameObject()->GetPosition().GetY(), goombaLists[i]->GetHealth());
//	////		printf_s("\n");
//	////		Sleep(1000);
//	////	}
//	////
//	////	while (true)
//	////	{
//	////		for (int i = 0; i < maxMonster; i++)
//	////		{
//	////			if (monsterLists[i] && monsterLists[i]->GetStatus() == "alive")
//	////			{
//	////				monController->SetGameObject(monsterLists[i]);
//	////				monController->UpdateGameObject();
//	////				monsterLists[i]->UpdateHealth();
//	////				printf_s("\n");
//	////				printf_s("Monster %s is currently at [%d, %d] with %d point(s) of health!\n", monsterLists[i]->GetName(), monController->GetGameObject()->GetPosition().GetX(), monController->GetGameObject()->GetPosition().GetY(), monsterLists[i]->GetHealth());
//	////				monsterLists[i]->CheckForDeath();
//	////			}
//	////		}
//	////
//	////		for (int i = 0; i < maxGoomba; i++)
//	////		{
//	////			if (goombaLists[i] && goombaLists[i]->GetStatus() == "alive")
//	////			{
//	////				gooController->SetGameObject(goombaLists[i]);
//	////				gooController->UpdateGameObject();
//	////				goombaLists[i]->UpdateHealth();
//	////				printf_s("\n");
//	////				printf_s("Goomba %d is currently at [%d, %d] with %d point(s) of health!\n", i + 1, gooController->GetGameObject()->GetPosition().GetX(), gooController->GetGameObject()->GetPosition().GetY(), goombaLists[i]->GetHealth());
//	////				goombaLists[i]->CheckForDeath();
//	////			}
//	////		}
//	////
//	////		printf_s("\n");
//	////		for (int i = 0; i < maxMonster; i++)
//	////		{
//	////			if (monsterLists[i] && monsterLists[i]->GetStatus() == "alive")
//	////			{
//	////				currentlyAlive++;
//	////			}
//	////		}
//	////
//	////		numMonster = currentlyAlive;
//	////		currentlyAlive = 0;
//	////
//	////		for (int i = 0; i < maxGoomba; i++)
//	////		{
//	////			if (goombaLists[i] && goombaLists[i]->GetStatus() == "alive")
//	////			{
//	////				currentlyAliveGoomba++;
//	////			}
//	////		}
//	////
//	////		numGoomba = currentlyAliveGoomba;
//	////		currentlyAliveGoomba = 0;
//	////
//	////		while (numMonster < minMonster)
//	////		{
//	////			int spawnIndex = RespawnMonsterP(monsterLists, monController);
//	////			if (spawnIndex != -1)
//	////			{
//	////				//char* newName = (char *)malloc(sizeof(char) * 12);
//	////				char* newName = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 12));
//	////				printf_s("Warning! A new monster just spawned! What do you want to call it? (Max length 10) ");
//	////				scanf_s("%s", newName, 10);
//	////				monsterLists[spawnIndex]->SetName(newName);
//	////				numMonster++;
//	////				printf_s("Now there are %d monsters in the dungeon. Take care!\n", numMonster);
//	////				printf_s("\n");
//	////			}
//	////		}
//	////
//	////		while (numGoomba < minGoomba)
//	////		{
//	////			int spawnIndex = RespawnGoombaP(goombaLists, gooController);
//	////			if (spawnIndex != -1)
//	////			{
//	////				printf_s("Warning! A new Goomba just spawned!\n");
//	////				numGoomba++;
//	////				printf_s("Now there are %d Goomba(s) in the dungeon. Take care!\n", numGoomba);
//	////				printf_s("\n");
//	////			}
//	////		}
//	////		
//	////
//	////		/*
//	////		// move monsters that are currently alive
//	////		for (int i = 0; i < 5; i++)
//	////		{
//	////			if (monsterList[i].GetStatus() == "alive")
//	////			{
//	////				monsterList[i].Move();
//	////				monsterList[i].CheckForDeath();
//	////				//DEBUG_LOG("This monster is at [%d, %d] now.\n", monsterList[i].GetPosition().GetX(), monsterList[i].GetPosition().GetY());
//	////			}
//	////		}
//	////
//	////		// recount the number of monsters that are still alive
//	////		for (int i = 0; i < 5; i++)
//	////		{
//	////			if (monsterList[i].GetStatus() == "alive")
//	////			{
//	////				currentlyAlive++;
//	////				//printf_s("Monster %s is currently at [%d, %d] with %d point(s) of health!\n", monsterList[i].GetName(), monsterList[i].GetPositionX(), monsterList[i].GetPositionY(), monsterList[i].GetHealth());
//	////				printf_s("Monster %s is currently at [%d, %d] with %d point(s) of health!\n", monsterList[i].GetName(), monsterList[i].GetPosition().GetX(), monsterList[i].GetPosition().GetY(), monsterList[i].GetHealth());
//	////			}
//	////		}
//	////
//	////		// reset to get ready for next round of counting
//	////		numMonster = currentlyAlive;
//	////		currentlyAlive = 0;
//	////
//	////		while (numMonster <= 2)
//	////		{
//	////			int spawnIndex = RespawnMonster(monsterList);
//	////			if (spawnIndex != -1)
//	////			{
//	////				//char* newName = (char *)malloc(sizeof(char) * 12);
//	////				char* newName = reinterpret_cast<char*>(allocator->allocate(sizeof(char) * 12));
//	////				printf_s("Warning! A new monster just spawned! What do you want to call it? (Max length 10) ");
//	////				scanf_s("%s", newName, 10);
//	////				monsterList[spawnIndex].SetName(newName);
//	////				numMonster++;
//	////				printf_s("Now there are %d monsters in the dungeon. Take care!\n", numMonster);
//	////			}
//	////		}
//	////		*/
//	////
//	////		printf_s("Now it's your turn! You are currently at [%d, %d]. What action do you want to take?\n", controller->GetGameObject()->GetPosition().GetX(), controller->GetGameObject()->GetPosition().GetY());
//	////		printf_s("\n");
//	////		printf_s("A to move left, D to move right, W to move up, S to move down, Q to flee from the dungeon.\n");
//	////		printf_s("\n");
//	////		controller->UpdateGameObject();
//	////		if (controller->GetExitSignal())
//	////		{
//	////			printf_s("You fled from the dungeon like a coward!\n");
//	////			printf_s("\n");
//	////			Sleep(3000);
//	////			_exit(0);
//	////		}	
//	////	}
//}