// Inline function definitions for PlayerController class

inline void PlayerController::SetGameObject(GameObject* targetObject)
{
	object = targetObject;
}

inline bool PlayerController::GetExitSignal()
{
	return isExit;
}

inline GameObject* PlayerController::GetGameObject() const
{
	return object;
}