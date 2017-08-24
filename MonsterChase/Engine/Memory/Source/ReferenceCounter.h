#ifndef REFERENCECOUNTER_H
#define REFERENCECOUNTER_H

namespace Engine
{
	class ReferenceCounter
	{
	public:
		ReferenceCounter() :
			smartCount(1),
			weakCount(0)
		{
		}

		~ReferenceCounter();

		long IncrementSmartReferenceCount();
		long DecrementSmartReferenceCount();
		long IncrementWeakReferenceCount();
		long DecrementWeakReferenceCount();

		long GetSmartCount();
		long GetWeakCount();
	private:
		long smartCount;
		long weakCount;
	};
}

#endif // !REFERENCECOUNTER_H
