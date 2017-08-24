// Inline function definitions for Monster class

/*
inline int Monster::GetPositionX() const
{
	return x;
}

inline int Monster::GetPositionY() const
{
	return y;
}
*/

/*
inline Point2D Monster::GetPosition() const
{
	return position;
}
*/

inline char *Monster::GetName() const
{
	return name;
}

inline char *Monster::GetStatus() const
{
	return status;
}

inline void Monster::CheckForDeath()
{
	if (health <= 0)
		status = "dead";
}

inline int Monster::GetHealth() const
{
	return health;
}

inline void Monster::UpdateHealth()
{
	if (health > 0)
		health--;
	else
		health = 0;
}

inline void Monster::Activate()
{
	status = "alive";
}

inline void Monster::ResetHealth()
{
	health = rand() % 5 + 3;
}

inline void Monster::ResetPosition()
{
	x = (float)(rand() % 100);
	y = (float)(rand() % 100);
	position = Point2D(x, y);
}

inline void Monster::SetName(const char* myname)
{
	name = const_cast<char*>(myname);
}