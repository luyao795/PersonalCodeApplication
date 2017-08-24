#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include "Point2D.h"
#include "GoombaController.h"

using namespace std;
using namespace Engine;

GoombaController::GoombaController()
{
	object = new GameObject();
	target = new GameObject();
}

GoombaController::~GoombaController()
{
	delete object;
	delete target;
	object = NULL;
	target = NULL;
}

void GoombaController::UpdateGameObject()
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

Point2D GoombaController::GetWanderDirection()
{
	// move horizontally, range [-2, 2]
	float deltaX = (float)(rand() % 5 - 2);
	// move vertically, range [-2, 2]
	float deltaY = (float)(rand() % 5 - 2);
	Point2D delta(deltaX, deltaY);
	return delta;
}