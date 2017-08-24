#ifndef WEAKPOINTER_H
#define WEAKPOINTER_H

#include <assert.h>
#include "ReferenceCounter.h"
#include "SmartPointer.h"

namespace Engine
{
	template<class T>
	class WeakPointer
	{
	public:
		WeakPointer(T* object) :
			curObject(object)
		{
		}

		WeakPointer(const SmartPointer<T>& smart) :
			curObject(smart.curObject),
			refCounter(smart.refCounter)
		{
			refCounter->IncrementWeakReferenceCount();
		}

		WeakPointer(const WeakPointer& other) :
			curObject(other.curObject),
			refCounter(other.refCounter)
		{
			refCounter->IncrementWeakReferenceCount();
		}

		WeakPointer(WeakPointer&& move) :
			curObject(move.curObject),
			refCounter(move.refCounter)
		{
			move.curObject = NULL;
			move.refCounter = NULL;
		}

		~WeakPointer()
		{
			ReleaseReference();
		}

		bool operator==(const WeakPointer& other) const
		{
			return ((curObject == other.curObject) && (refCounter == other.refCounter));
		}

		T& operator=(const WeakPointer& other)
		{
			if (this != &other)
			{
				ReleaseReference();
				AcquireReference(other);
			}
			return *this;
		}

		SmartPointer<T> AcquireSmart() const
		{
			if (refCounter->GetSmartCount() > 0)
			{
				refCounter->IncrementSmartReferenceCount();
				return SmartPointer<T>(curObject, refCounter);
			}
			else
				return SmartPointer<T>(NULL);
		}

		void Dereference()
		{
			if (refCounter)
			{
				assert(refCounter->GetWeakCount() > 0);
				refCounter->DecrementWeakReferenceCount();
				if (refCounter->GetSmartCount() == 0 && refCounter->GetWeakCount() == 0)
				{
					delete refCounter;
					refCounter = NULL;
				}
			}
		}

		void SetReferenceCounter(ReferenceCounter* counter)
		{
			refCounter = counter;
		}

		ReferenceCounter* GetReferenceCounter()
		{
			return refCounter;
		}

		void ReleaseReference()
		{
			Dereference();
		}

		void AcquireReference(const WeakPointer& other)
		{
			refCounter = other.refCounter;
			curObject = other.curObject;
			refCounter->IncrementWeakReferenceCount();
		}
	private:
		T* curObject;
		ReferenceCounter* refCounter;
	};
}

#endif // !WEAKPOINTER_H
