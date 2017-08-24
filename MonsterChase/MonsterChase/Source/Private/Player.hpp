// Inline function definitions for Player class

/*
inline int Player::GetPositionX() const
{
	return x;
}

inline int Player::GetPositionY() const
{
	return y;
}
*/

inline char *Player::GetStatus() const
{
	return status;
}

inline char *Player::GetName() const
{
	return name;
}

inline int Player::GetHealth() const
{
	return health;
}

/*
inline Point2D Player::GetPosition() const
{
	return position;
}
*/

inline void Player::SetName(const char *myname)
{
	name = const_cast<char*>(myname);
}

inline void Player::Kill()
{
	if (health <= 0)
		status = "dead";
}