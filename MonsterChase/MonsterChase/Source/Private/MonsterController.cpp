#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "Point2D.h"
#include "MonsterController.h"

using namespace std;
using namespace Engine;

MonsterController::MonsterController()
{
	object = new GameObject();
	target = new GameObject();
}

MonsterController::~MonsterController()
{
	delete object;
	delete target;
	object = NULL;
	target = NULL;
}

void MonsterController::UpdateGameObject()
{
	Point2D dir;
	if (target)
	{
		dir = target->GetPosition() - object->GetPosition();
		dir = dir.Normalize();
	}
	else
	{
		dir = GetWanderDirection();
	}
	object->SetPosition(object->GetPosition() + dir);
}

Point2D MonsterController::GetWanderDirection()
{
	// move horizontally, range [-2, 2]
	float deltaX = (float)(rand() % 5 - 2);
	// move vertically, range [-2, 2]
	float deltaY = (float)(rand() % 5 - 2);
	Point2D delta(deltaX, deltaY);
	return delta;
}