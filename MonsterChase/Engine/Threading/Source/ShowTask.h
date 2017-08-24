#ifndef SHOWTASK_H
#define SHOWTASK_H

#include "ThreadedFileProcessor.h"
#include "Mutex.h"

namespace Engine
{

	class ShowTask : public Azra::ThreadedFileProcessor::LoadTask
	{
	public:
		ShowTask(const char * i_pFilename, PhysicsInfo * pInfo, std::vector<SmartPointer<GameObject>> & olist, Mutex & taskMutex) :
			Azra::ThreadedFileProcessor::LoadTask(i_pFilename),
			fileName(i_pFilename),
			info(pInfo),
			list(olist),
			mutex(taskMutex)
		{
		}
		virtual void ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes);
	private:
		PhysicsInfo * info;
		std::vector<SmartPointer<GameObject>> & list;
		const char * fileName;
		Mutex & mutex;
	};

}

#endif // SHOWTASK_H