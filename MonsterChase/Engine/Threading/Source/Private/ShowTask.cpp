#include <assert.h>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <Windows.h>
#include "GameObject.h"
#include "PhysicsInfo.h"
#include "GameObjectCreator.h"
#include "ThreadedFileProcessor.h"
#include "ShowTask.h"

using namespace std;

namespace Engine
{
	//class GameObjectCreator;

	void ShowTask::ProcessFileContents(uint8_t * i_pBuffer, uint32_t i_BufferBytes)
	{
		if ((i_pBuffer != NULL) && (i_BufferBytes > 0))
		{
			/*char * temp = new char[i_BufferBytes + 1];
			memcpy(temp, i_pBuffer, i_BufferBytes);
			temp[i_BufferBytes] = 0;
			printf("%s contains:\n%s", GetFileName(), temp);
			delete temp;*/

			mutex.Acquire();
			SmartPointer<GameObject> * objP = CreateGameObject(fileName, info);
			list.push_back(*objP);
			mutex.Release();
		}
	}

}