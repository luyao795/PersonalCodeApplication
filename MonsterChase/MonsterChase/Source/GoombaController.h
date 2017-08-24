#ifndef GOOMBACONTROLLER_H
#define GOOMBACONTROLLER_H

using namespace std;
using namespace Engine;

#include "GameObjectController.h"

class GoombaController : public GameObjectController
{
public:
	GoombaController();
	~GoombaController();
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

#include "GoombaController.hpp"
#endif // !GOOMBACONTROLLER_H

