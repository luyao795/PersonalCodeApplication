#ifndef GAMEOBJECTCONTROLLER_H
#define GAMEOBJECTCONTROLLER_H

#include "GameObject.h"

namespace Engine
{
	class GameObjectController
	{
	public:
		virtual void SetGameObject(GameObject* object) = 0;
		virtual void UpdateGameObject() = 0;
	};
}

#endif // !GAMEOBJECTCONTROLLER_H
