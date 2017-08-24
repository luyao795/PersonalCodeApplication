#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

using namespace std;
using namespace Engine;

#include "GameObjectController.h"

class PlayerController : public GameObjectController
{
public:
	PlayerController();
	~PlayerController();
	inline void SetGameObject(GameObject* targetObject) override;
	inline bool GetExitSignal();
	inline GameObject* GetGameObject() const;
	void UpdateGameObject() override;
	Point2D GetMovementDirection();

private:
	GameObject* object;
	bool isExit;
};

#include "PlayerController.hpp"
#endif // !PLAYERCONTROLLER_H
