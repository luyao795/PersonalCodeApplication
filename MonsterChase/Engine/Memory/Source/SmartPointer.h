#ifndef SMARTPOINTER_H
#define SMARTPOINTER_H

#include <assert.h>
#include "ReferenceCounter.h"

namespace Engine
{
	template<class T>
	class SmartPointer
	{
	public:
		SmartPointer(T* object) :
			curObject(object)
		{
		}

		SmartPointer(T* object, ReferenceCounter* counter) :
			curObject(object),
			refCounter(counter)
		{
			// The same effect is achieved in AcquireSmart() function.
			//refCounter->IncrementSmartReferenceCount();
		}

		SmartPointer(const SmartPointer& other) :
			curObject(other.curObject),
			refCounter(other.refCounter)
		{
			refCounter->IncrementSmartReferenceCount();
		}

		SmartPointer(SmartPointer&& move) :
			curObject(move.curObject),
			refCounter(move.refCounter)
		{
			move.curObject = NULL;
			move.refCounter = NULL;
		}

		~SmartPointer()
		{
			ReleaseReference();
		}

		T* GetGameObject()
		{
			return curObject;
		}

		T* operator->()
		{
			assert(curObject != NULL);
			return curObject;
		}

		T& operator*()
		{
			assert(curObject != NULL);
			return *curObject;
		}

		T& operator=(const SmartPointer& other)
		{
			if (this != &other)
			{
				ReleaseReference();
				AcquireReference(other);
			}
			return *this;
		}

		bool operator==(const SmartPointer& other) const
		{
			return ((curObject == other.curObject) && (refCounter == other.refCounter));
		}

		void Dereference()
		{
			if (refCounter)
			{
				assert(refCounter->GetSmartCount() > 0);
				long tempCount = refCounter->DecrementSmartReferenceCount();
				if (tempCount == 0)
				{
					if (curObject)
					{
						delete curObject;
						curObject = NULL;
						/*if (refCounter->GetWeakCount() == 0)
						{
							delete refCounter;
							refCounter = NULL;
						}*/
					}
				}
			}
		}

		void SetReferenceCounter(ReferenceCounter* counter)
		{
			refCounter = counter;
		}

		void SetGameObject(T* object)
		{
			curObject = object;
		}

		ReferenceCounter* GetReferenceCounter()
		{
			return refCounter;
		}

		void ReleaseReference()
		{
			Dereference();
		}

		void AcquireReference(const SmartPointer& other)
		{
			refCounter = other.refCounter;
			curObject = other.curObject;
			refCounter->IncrementSmartReferenceCount();
		}
	private:
		T* curObject;
		ReferenceCounter* refCounter;
		template<class T>
		friend class WeakPointer;
	};
}

#endif // !SMARTPOINTER_H