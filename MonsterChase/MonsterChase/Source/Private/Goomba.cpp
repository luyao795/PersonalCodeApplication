#include <malloc.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>
#include <algorithm>
#include "Point2D.h"
#include "DebugPrint.h"
#include "Goomba.h"
#include "HashedString.h"
#include "MessagingSystem.h"
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

Goomba::Goomba()
{
	status = (char*)alloc->allocate(sizeof(char) * 5);
	status = "alive";
	health = 20;
	MessagingSystem msgSys = MessagingSystem();
	msgSys.AddMessageHandler("Actor Created", std::bind(&Goomba::HandleCreationMessage, this, std::placeholders::_1), Message::ACTOR_CREATED);
}

Goomba::Goomba(const Goomba& copy) :
	status(_strdup(copy.status)),
	health(copy.health)
{

}

Goomba::Goomba(Goomba&& move) :
	status(move.status),
	health(move.health)
{
	move.status = NULL;
}

Goomba::~Goomba()
{
	delete status;
	status = NULL;
}

Goomba& Goomba::operator=(Goomba& copy)
{
	status = _strdup(copy.status);
	health = copy.health;

	return *this;
}

Goomba& Goomba::operator=(Goomba&& move)
{
	swap(status, move.status);
	swap(health, move.health);

	return *this;
}

void Goomba::HandleCreationMessage(const HashedString & msg)
{
	OutputDebugStringA(msg.GetString());
}
