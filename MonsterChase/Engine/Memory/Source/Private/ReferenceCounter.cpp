#include <assert.h>
#include "ReferenceCounter.h"
#include "GameObject.h"

using namespace std;

namespace Engine
{
	ReferenceCounter::~ReferenceCounter()
	{
	}

	long ReferenceCounter::IncrementSmartReferenceCount()
	{
		smartCount++;
		return smartCount;
	}

	long ReferenceCounter::DecrementSmartReferenceCount()
	{
		assert(smartCount > 0);
		smartCount--;
		if (smartCount == 0 && weakCount == 0)
			delete this;
		return smartCount;
	}

	long ReferenceCounter::IncrementWeakReferenceCount()
	{
		weakCount++;
		return weakCount;
	}

	long ReferenceCounter::DecrementWeakReferenceCount()
	{
		assert(weakCount > 0);
		weakCount--;
		if (smartCount == 0 && weakCount == 0)
			delete this;
		return weakCount;
	}

	long ReferenceCounter::GetSmartCount()
	{
		return smartCount;
	}

	long ReferenceCounter::GetWeakCount()
	{
		return weakCount;
	}
}