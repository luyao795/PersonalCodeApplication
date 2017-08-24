#ifndef HASHEDSTRING_H
#define HASHEDSTRING_H

#include <assert.h>
#include <stdint.h>
#include <string.h>
#include "PooledString.h"

namespace Engine
{
	class HashedString
	{
	public:
		HashedString(const char * string) :
			stringH(string)
		{
		}

		HashedString(const PooledString & pooled) :
			stringH(pooled.GetString())
		{
		}

		HashedString(const HashedString & hashed) :
			stringH(hashed.stringH)
		{
		}

		const char * GetString() const
		{
			return stringH;
		}

		HashedString & operator=(const HashedString & other)
		{
			stringH = other.stringH;
		}

		bool operator==(const HashedString & other)
		{
			return stringH == other.stringH;
		}

		bool operator==(const char * other)
		{
			return stringH == other;
		}

		bool operator==(const PooledString & other)
		{
			return stringH == other.GetString();
		}

		operator bool() const
		{
			return stringH == nullptr;
		}

		unsigned int Hash(const char * i_string)
		{
			assert(i_string);

			return Hash(reinterpret_cast<void *>(const_cast<char *>(i_string)), (strlen(i_string)));
		}

		unsigned int Hash(const void * i_bytes, size_t i_bytecount)
		{
			// FNV hash, http://isthe.com/chongo/tech/comp/fnv/

			const uint8_t * p = static_cast<const uint8_t *>(i_bytes);
			unsigned int hash = 2166136261;

			for (unsigned int i = 0; i < i_bytecount; ++i)
				hash = 16777619 * (hash ^ p[i]);

			return hash ^ (hash >> 16);
		}

	private:
		const char * stringH;
	};
}

#endif // !HASHEDSTRING_H
