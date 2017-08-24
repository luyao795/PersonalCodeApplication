#ifndef MONSTER_H
#define MONSTER_H

#include "GameObject.h"

using namespace std;
using namespace Engine;

#pragma once
class Monster : public GameObject
{
	
public:
	Monster();
	Monster(const Monster& copy);
	Monster(Monster&& move);
	~Monster();

	void Move();
	void GenerateName();
	//inline int GetPositionX() const;
	//inline int GetPositionY() const;
	//inline Point2D GetPosition() const;
	inline char *GetName() const;
	inline char *GetStatus() const;
	inline void CheckForDeath();
	inline int GetHealth() const;
	inline void UpdateHealth();
	inline void SetName(const char* myname);
	inline void Activate();
	inline void ResetHealth();
	inline void ResetPosition();

	Monster& operator=(Monster& copy);
	Monster& operator=(Monster&& move);

private:
	float x;
	float y;
	char *name;
	Point2D position;
	char *status;
	int health;
	static const int length = 10;
};

#include "Monster.hpp"
#endif