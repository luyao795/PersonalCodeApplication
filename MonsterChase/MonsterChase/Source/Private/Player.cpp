#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <Windows.h>
#include <stdarg.h>
#include <stdio.h>
#include "Point2D.h"
#include "Player.h"
#include "BlockAllocator.h"
#include "FSAManager.h"

#define ALLOCATE_SIZE 1024

#ifdef _DEBUG
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(msg, cond)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // DEBUG

using namespace std;
using namespace Engine;

static BlockAllocator* alloc = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
static FSAManager* fsa = FSAManager::create();

Player::Player()
{
	//name = (char*)malloc(sizeof(char) * 100);
	name = (char*)alloc->allocate(sizeof(char) * 100);
	//status = (char*)malloc(sizeof(char) * 5);
	status = (char*)alloc->allocate(sizeof(char) * 5);
	x = 0.0f;
	y = 0.0f;
	position = Point2D();
	health = 10;
	name = "";
	status = "alive";
}

Player::Player(const float initX, const float initY)
{
	//name = (char*)malloc(sizeof(char) * 10);
	name = (char*)alloc->allocate(sizeof(char) * 100);
	//status = (char*)malloc(sizeof(char) * 5);
	status = (char*)alloc->allocate(sizeof(char) * 5);
	/*if (initX >= 0.0f && initX < 100.0f && initY >= 0.0f && initY < 100.0f)
	{*/
		x = initX;
		y = initY;
		position = Point2D(initX, initY);
	/*}
	else
	{
		x = 0.0f;
		y = 0.0f;
		position = Point2D();
	}*/
	health = 10;
	status = "alive";
	name = "";
}

Player::~Player()
{
	delete name;
	delete status;
	name = NULL;
	status = NULL;
}

void Player::MoveUp()
{
	Point2D delta(0.0f, 1.0f);
	position = position + delta;
	//y += 1;
	//if (y > 99)
	//	y = 99;
	if (position.GetY() > 99.0f)
		position.SetY(99.0f);
}

void Player::MoveDown()
{
	Point2D delta(0.0f, 1.0f);
	position = position - delta;
	//y -= 1;
	//if (y < 0)
	//	y = 0;
	if (position.GetY() < 0.0f)
		position.SetY(0.0f);
}

void Player::MoveLeft()
{
	Point2D delta(1.0f, 0.0f);
	position = position - delta;
	//x -= 1;
	//if (x < 0)
	//	x = 0;
	if (position.GetX() < 0.0f)
		position.SetX(0.0f);
}

void Player::MoveRight()
{
	Point2D delta(1.0f, 0.0f);
	position = position + delta;
	//x += 1;
	//if (x > 99)
	//	x = 99;
	if (position.GetX() > 99.0f)
		position.SetX(99.0f);
}


