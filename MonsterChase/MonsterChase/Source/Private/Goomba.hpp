// Inline function definitions for Goomba class

inline int Goomba::GetHealth() const
{
	return health;
}

inline char* Goomba::GetStatus() const
{
	return status;
}

inline void Goomba::CheckForDeath()
{
	if (health <= 0)
		status = "dead";
}

inline void Goomba::UpdateHealth()
{
	if (health > 0)
		health -= 2;
	else
		health = 0;
}