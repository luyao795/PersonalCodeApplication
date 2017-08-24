// Inline function definitions for GoombaController class

inline void GoombaController::SetGameObject(GameObject* targetObject)
{
	object = targetObject;
}

inline void GoombaController::SetFocusObject(GameObject* targetObject)
{
	target = targetObject;
}

inline void GoombaController::SetGameObjectPosition()
{
	object->SetPosition(Point2D((float)(rand() % 100), (float)(rand() % 100)));
}

inline GameObject* GoombaController::GetGameObject() const
{
	return object;
}

inline GameObject* GoombaController::GetFocusObject() const
{
	return target;
}
