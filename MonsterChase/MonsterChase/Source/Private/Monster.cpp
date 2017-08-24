#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include "DebugPrint.h"
#include "Point2D.h"
#include "Monster.h"
#include "BlockAllocator.h"
#include "FSAManager.h"

#define ALLOCATE_SIZE 1024

#ifdef _DEBUG
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#endif // DEBUG

using namespace std;
using namespace Engine;

static BlockAllocator* alloc = BlockAllocator::create(ALLOCATE_SIZE * ALLOCATE_SIZE, ALLOCATE_SIZE * 2);
static FSAManager* fsa = FSAManager::create();

Monster::Monster()
{
	//name = (char *)malloc(sizeof(char) * 10);
	name = (char*)alloc->allocate(sizeof(char) * 12);
	//status = (char *)malloc(sizeof(char) * 5);
	status = (char*)alloc->allocate(sizeof(char) * 5);
	x = (float)(rand() % 100);
	y = (float)(rand() % 100);
	name = "";
	position = Point2D(x, y);
	status = "alive";
	health = rand() % 4 + 8;
}

Monster::Monster(const Monster& copy) :
	name(_strdup(copy.name ? copy.name : "Monster")),
	position(copy.position),
	status(_strdup(copy.status)),
	health(copy.health)
{
	printf_s("Calling copy constructor.\n");
}

Monster::Monster(Monster&& move) :
	name(move.name),
	position(move.position),
	status(move.status),
	health(move.health)
{
	move.name = NULL;
	move.status = NULL;
	printf_s("Calling move constructor.\n");
}

Monster::~Monster()
{
	delete name;
	delete status;
	name = NULL;
	status = NULL;
}

void Monster::Move()
{
	DEBUG_LOG("Monster Status BEFORE Move: [Health: %d] [Status: %s] [Position.X: %d] [Position.Y: %d]", health, status, position.GetX(), position.GetY());
	// move horizontally, range [-2, 2]
	//x += rand() % 5 - 2;
	float deltaX = (float)(rand() % 5 - 2);
	// move vertically, range [-2, 2]
	//y += rand() % 5 - 2;
	float deltaY = (float)(rand() % 5 - 2);
	Point2D delta(deltaX, deltaY);
	position = position + delta;
	//position.MoveX(deltaX);
	//position.MoveY(deltaY);
	// boundary check
	//if (x > 99)
	//	x = 99;
	//if (x < 0)
	//	x = 0;
	//if (y > 99)
	//	y = 99;
	//if (y < 0)
	//	y = 0;
	if (position.GetY() > 99.0f)
		position.SetY(99.0f);
	if (position.GetY() < 0.0f)
		position.SetY(0.0f);
	if (position.GetX() < 0.0f)
		position.SetX(0.0f);
	if (position.GetX() > 99.0f)
		position.SetX(99.0f);
	health--;
	DEBUG_LOG("Monster Status AFTER Move: [Health: %d] [Status: %s] [Position.X: %d] [Position.Y: %d]", health, status, position.GetX(), position.GetY());
}

void Monster::GenerateName()
{
	char mname[length] = { 0 };

	// First letter should be in uppercase
	mname[0] = (rand() % 26 + 65);

	// The rest would remain in lowercase
	for (int i = 1; i < length; i++)
	{
		mname[i] = (rand() % 26 + 97);
	}

	// copy char array into char pointer
	name = _strdup(mname);
	name = (char *)realloc(name, sizeof(char) * length);
}

Monster& Monster::operator=(Monster& copy)
{
	name = _strdup(copy.name ? copy.name : "Monster");
	status = _strdup(copy.status);
	position = copy.position;
	health = copy.health;
	printf_s("Calling copy assignment operator.\n");
	return *this;
}

Monster& Monster::operator=(Monster&& move)
{
	swap(name, move.name);
	swap(status, move.status);
	swap(position, move.position);
	swap(health, move.health);
	printf_s("Calling move assignment operator.\n");
	return *this;
}



