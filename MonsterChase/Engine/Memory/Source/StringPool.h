#ifndef STRINGPOOL_H
#define STRINGPOOL_H

namespace Engine
{
	class StringPool
	{
	public:
		static StringPool * create(size_t bytesInPool);
		~StringPool();

		// find string in pool - adding it if it's not there
		const char * add(const char * string);
		// find string in pool - don't add if it's not there
		const char * find(const char * string);

		void addStringInfo(const char * string);

		static StringPool* getInstance();

	private:
		StringPool(uint8_t * pool, size_t poolSize);
		static StringPool* instance;
		uint8_t * startPool;
		uint8_t * endPool;
		uint8_t * endString;
		size_t size;
	};
}

#endif // !STRINGPOOL_H
