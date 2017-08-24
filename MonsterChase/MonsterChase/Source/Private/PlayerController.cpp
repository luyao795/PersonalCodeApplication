#include <conio.h>
#include <stdio.h>
#include "Point2D.h"
#include "GameObjectController.h"
#include "PlayerController.h"

using namespace std;
using namespace Engine;

PlayerController::PlayerController()
{
	object = new GameObject();
	isExit = false;
}

PlayerController::~PlayerController()
{
	delete object;
	object = NULL;
}

void PlayerController::UpdateGameObject()
{
	if (object)
	{
		Point2D dir = GetMovementDirection();
		object->SetPosition(object->GetPosition() + dir);
	}
}

Point2D PlayerController::GetMovementDirection()
{
	int press = _getch();
	Point2D dir;
	if (press == 'a' || press == 'A')
	{
		dir = Point2D(-1, 0);
	}
	else if (press == 'd' || press == 'D')
	{
		dir = Point2D(1, 0);
	}
	else if (press == 'w' || press == 'W')
	{
		dir = Point2D(0, 1);
	}
	else if (press == 's' || press == 'S')
	{
		dir = Point2D(0, -1);
	}
	else if (press == 'q' || press == 'Q')
	{
		dir = Point2D(0, 0);
		isExit = true;
	}
	return dir;
}