#ifndef POOLEDSTRING_H
#define POOLEDSTRING_H

#include "StringPool.h"

namespace Engine
{
	class PooledString
	{
	public:
		PooledString(const char * string)
		{
			poolInstance = StringPool::getInstance();
			if (!poolInstance)
				poolInstance = StringPool::create(1024 * 1024);
			stringPos = poolInstance->add(string);
		}

		PooledString(const PooledString & other) :
			stringPos(other.stringPos)
		{
			poolInstance = StringPool::getInstance();
		}

		const char * GetString() const
		{
			return stringPos;
		}

		PooledString & operator=(const PooledString & other)
		{
			stringPos = other.stringPos;
		}

		bool operator==(const PooledString & other)
		{
			return stringPos == other.stringPos;
		}

		bool operator==(const char * other)
		{
			return stringPos == other;
		}

		operator bool() const
		{
			return stringPos == nullptr;
		}

	private:
		static StringPool* poolInstance;
		// Potentially problematic as this is const and it's been modified in constructor.
		const char * stringPos;
	};
}

#endif // !POOLEDSTRING_H
