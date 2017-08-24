#ifndef HANDLER_H
#define HANDLER_H

namespace Engine
{
		void StartEngine();

		void CloseEngine();

		static BlockAllocator* allocator;

		static FSAManager* manager;
}
#endif // !HANDLER_H
