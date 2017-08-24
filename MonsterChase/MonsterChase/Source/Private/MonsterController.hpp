// Inline function definitions for MonsterController class

inline void MonsterController::SetGameObject(GameObject* targetObject)
{
	object = targetObject;
}

inline void MonsterController::SetFocusObject(GameObject* targetObject)
{
	target = targetObject;
}

inline void MonsterController::SetGameObjectPosition()
{
	object->SetPosition(Point2D((float)(rand() % 100), (float)(rand() % 100)));
}

inline GameObject* MonsterController::GetGameObject() const
{
	return object;
}

inline GameObject* MonsterController::GetFocusObject() const
{
	return target;
}