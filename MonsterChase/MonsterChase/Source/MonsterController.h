#ifndef MONSTERCONTROLLER_H
#define MONSTERCONTROLLER_H

using namespace std;
using namespace Engine;

#include "GameObjectController.h"

class MonsterController : public GameObjectController
{
public:
	MonsterController();
	~MonsterController();
	inline void SetGameObject(GameObject* targetObject) override;
	inline void SetGameObjectPosition();
	inline void SetFocusObject(GameObject* targetObject);
	inline GameObject* GetGameObject() const;
	inline GameObject* GetFocusObject() const;
	void UpdateGameObject() override;
	Point2D GetWanderDirection();

private:
	GameObject* object;
	GameObject* target;
};

#include "MonsterController.hpp"
#endif // !MONSTERCONTROLLER_H