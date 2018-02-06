README file for FinalExam

Note: 
Regular BlockAllocator is a singleton that will only have 1 instance alive at the same time.
FSAManager is a singleton that will only have 1 instance alive at the same time.

BitArray and FixedSizeAllocator are not static, meaning there will be multiple BitArrays and FixedSizeAllocators alive at the same time.
However, if not being created separately, there will be no standalone BirArray existing, each FixedSizeAllocator will have its own child BitArray.
By default, there will be 4 FixedSizeAllocator created by calling FSAManager->createFSA() [Located at line 55 in FSAManager.cpp]

For placement new, an additional boolean value will be taken to determine whether the memory is from system or BlockAllocator [Located at lines 33 and 74 in MemoryOperator.cpp]
If boolean == true then the memory will be taken from system, otherwise the memory will be taken from BlockAllocator.

For BlockAllocator, allocate(size_t) [Located at line 67 in BlockAllocator.cpp] will use selection sort to sort the free descriptor list based on block size and give back the first one that meets size requirement;
collect() [Located at line 283 in BlockAllocator.cpp] will sort free descriptor list by block base address and combine those that are consecutive.

For regular new operators that got overrode [Located at lines 21, 50 and 62], if allowed to use FSA to allocate memory, they will check whether that FSA is full or not, if it's not then they will use the corresponding FSA, otherwise they will use regular BlockAllocator instead.

Important:
Because BlockAllocator is a singleton, the create function [Located at line 42 in BlockAllocator.cpp] will check whether the signleton is NULL. If it is then create one with given parameters, otherwise just return the existing one.
That means whenever you want to change the parameters of the singleton, you will have to change, just in case, parameters for all create function calls. (There is one in Player.cpp, one in Monster.cpp, one in Goomba.cpp, one in Main.cpp)
