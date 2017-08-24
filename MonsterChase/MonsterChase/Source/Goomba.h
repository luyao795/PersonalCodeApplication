#ifndef GOOMBA_H
#define GOOMBA_H

#include "HashedString.h"
#include "GameObject.h"

using namespace std;
using namespace Engine;

class Goomba : public GameObject
{
public:
	Goomba();
	Goomba(const Goomba& copy);
	Goomba(Goomba&& move);
	~Goomba();
	inline int GetHealth() const;
	inline char* GetStatus() const;
	inline void CheckForDeath();
	inline void UpdateHealth();

	Goomba& operator=(Goomba& copy);
	Goomba& operator=(Goomba&& move);

	void HandleCreationMessage(const HashedString & msg);

private:
	char* status;
	int health;
};

#include "Goomba.hpp"
#endif // !GOOMBA_H
