#ifndef PLAYER_H
#define PLAYER_H

using namespace std;
using namespace Engine;

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player();
	Player(const float initX, const float initY);
	~Player();

	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();
	inline void SetName(const char *myname);
	//inline int GetPositionX() const;
	//inline int GetPositionY() const;
	//inline Point2D GetPosition() const;
	inline char *GetStatus() const;
	inline char *GetName() const;
	inline void Kill();
	inline int GetHealth() const;
	

private:
	float x;
	float y;
	Point2D position;
	char *name;
	char *status;
	int health;
};

#include "Player.hpp"
#endif // !PLAYER_H