#ifndef MEMORYOPERATOR_H
#define MEMORYOPERATOR_H

#include "FixedSizeAllocator.h"

void* operator new(size_t size);
void* operator new(size_t size, bool allocation);
void* operator new(size_t size, const char* file, const char* func, const unsigned int line);
void* operator new[](size_t size);
void* operator new[](size_t size, bool allocation);
void operator delete(void* pointer);
void operator delete(void* pointer, bool allocation);
void operator delete(void* pointer, const char* file, const char* func, const unsigned int line);
void operator delete[](void* pointer);
void operator delete[](void* pointer, bool allocation);


#endif // !MEMORYOPERATOR_H