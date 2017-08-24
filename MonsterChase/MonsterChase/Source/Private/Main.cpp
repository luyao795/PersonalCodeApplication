#define _USE_MATH_DEFINES
#include <Windows.h>
#include <assert.h>
#include <conio.h>
#include <malloc.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <vector>
#include <algorithm>
#include "BlockAllocator.h"
#include "MemoryOperator.h"
#include "FSAManager.h"
#include "BitArray.h"
#include "Point2D.h"
#include "GameObject.h"
#include "GameObjectController.h"
#include "PlayerController.h"
#include "MonsterController.h"
#include "GoombaController.h"
#include "Player.h"
#include "Monster.h"
#include "Goomba.h"
#include "Handler.h"
#include "PhysicsInfo.h"
#include "SmartPointer.h"
#include "WeakPointer.h"
#include "Timer.h"
#include "Input.h"
#include "StringPool.h"
#include "lua.hpp"
#include "GameObjectCreator.h"
#include "ShowTask.h"
#include "Matrix4X4.h"
#include "SpriteLoader.h"
#include "Sprite.h"
#include "CollisionChecker.h"
#include "DebugPrint.h"
#include "SIMDVector4D.h"
#include "SIMDMatrix4X4.h"
#include "ValidityErrorChecker.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC  
#include <crtdbg.h>
#define DEBUG_LOG(fmt, ...) Engine::DebugPrint(__FILE__, __FUNCTION__, __LINE__, fmt, __VA_ARGS__)
#define ASSERT(msg, cond) assert(cond && msg)
#define TRACK_NEW (__FILE__, __FUNCTION__, __LINE__)
#else
#define DEBUG_LOG(fmt, ...) void(0)
#define ASSERT(cond, msg) void(0)
#define TRACK_NEW
#endif // _DEBUG

#include "GLib.h"

#define CONSTANT_FRAMETIME

using namespace std;
using namespace Engine;

//int RespawnMonster(Monster list[]);

void MoveToAddList(vector<SmartPointer<GameObject>> & loadQ, vector<SmartPointer<GameObject>> & addQ, Mutex & mutex);

void UpdatePhysics(vector<PhysicsInfo *> pInfoList, Point2D force, float dt);

void UpdatePhysicsIndividual(PhysicsInfo * pInfo, Point2D force, float dt);

void UpdateBoundingBoxIndividual(Sprite * image);

int RespawnMonsterP(Monster* list[], MonsterController* monController);

int RespawnGoombaP(Goomba* list[], GoombaController* gooController);

void TestKeyCallback(unsigned int i_VKeyID, bool bWentDown)
{
#ifdef _DEBUG
	const size_t	lenBuffer = 65;
	char			Buffer[lenBuffer];

	sprintf_s(Buffer, lenBuffer, "VKey 0x%04x went %s\n", i_VKeyID, bWentDown ? "down" : "up");
	OutputDebugStringA(Buffer);
#endif // __DEBUG
}

int WINAPI wWinMain(HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow)
{
	StartEngine();

	bool bSuccess = GLib::Initialize(i_hInstance, i_nCmdShow, "Triple Battle", -1, 1366, 768);

	if (bSuccess)
	{
		// Set a callback for notification of key presses
		GLib::SetKeyStateChangeCallback(TestKeyCallback);

		SpriteLoader * loader = new SpriteLoader();

		Point2D locations[] = { Point2D(-400.0f, 200.0f) , Point2D(-200.0f, 200.0f) , Point2D(0.0f, 200.0f) , Point2D(200.0f, 200.0f) , Point2D(400.0f, 200.0f) , Point2D(-400.0f, 0.0f) , Point2D(-200.0f, 0.0f) , Point2D(0.0f, 0.0f) , Point2D(200.0f, 0.0f) , Point2D(400.0f, 0.0f) , Point2D(-400.0f, -200.0f) , Point2D(-200.0f, -200.0f) , Point2D(0.0f, -200.0f) , Point2D(200.0f, -200.0f) , Point2D(400.0f, -200.0f) };
		int locationSize = 15;

		float forceV = 0.5f;

		Matrix4X4 * mat = new Matrix4X4();
		Matrix4X4 identity = mat->Identity();

		Sprite * goodG = new Sprite();
		goodG->SetImage(loader->CreateSprite("Externals\\Images\\GoodGuy.dds"));
		goodG->SetSize(Vector3D(static_cast<float>(loader->GetWidth()), static_cast<float>(loader->GetHeight()), 0.0f));
		goodG->SetBoundingBoxExtent(Vector3D(goodG->GetSize().GetX() / 2, goodG->GetSize().GetY() / 2, 0.0f));

		Sprite * goomba = new Sprite();
		goomba->SetImage(loader->CreateSprite("Externals\\Images\\Paddle.dds"));
		goomba->SetSize(Vector3D(static_cast<float>(loader->GetWidth()), static_cast<float>(loader->GetHeight()), 0.0f));
		goomba->SetBoundingBoxExtent(Vector3D(goomba->GetSize().GetX() / 2, goomba->GetSize().GetY() / 2, 0.0f));

		CollisionChecker * checker = new CollisionChecker();

		// Create a couple of sprites using our own helper routine CreateSprite
		//GLib::Sprites::Sprite * pGoodGuy = CreateSprite("Externals\\Images\\GoodGuy.dds");
		//GLib::Sprites::Sprite * pBadGuy = CreateSprite("Externals\\Images\\BadGuy.dds");
		//GLib::Sprites::Sprite * pGoomba = CreateSprite("Externals\\Images\\Goomba.dds");

		ReferenceCounter * rc = new ReferenceCounter();
		PhysicsInfo * newPI = new PhysicsInfo(0.0f, 0.0f);
		SmartPointer<GameObject> * newP = CreateGameObject("Externals\\Data\\Player.lua", newPI);
		newP->SetReferenceCounter(rc);

		Input* in = new Input();
		in->Read();

		Monster *monsterLists[10];

		Goomba *goombaLists[5];

		for (int i = 0; i < 10; i++)
		{
			monsterLists[i] = NULL;
		}

		for (int i = 0; i < 5; i++)
		{
			goombaLists[i] = NULL;
		}

		Player *pp = new TRACK_NEW Player();

		PlayerController *controller = new PlayerController();
		//MonsterController *monController = new MonsterController();
		GoombaController *gooController = new GoombaController();

		controller->SetGameObject(pp);
		//monController->SetFocusObject(pp);
		gooController->SetFocusObject(pp);
		for (int i = 0; i < 5; i++)
		{
			goombaLists[i] = new Goomba();
			gooController->SetGameObject(goombaLists[i]);
			//gooController->SetGameObjectPosition();
			goombaLists[i]->SetPosition(Point2D(-400.0f, 200.0f));
		}
		//monController->SetGameObject(monsterLists[0]);
		gooController->SetGameObject(goombaLists[0]);

		static Timer* t = Timer::Create();
		t->GetCounter();
		t->GetFrequency();
		t->CalculateFrameTimeInMS();

		float dt = t->GetLastFrameTimeInMS();

		/**/
		Azra::ThreadedFileProcessor &Processor = Azra::ThreadedFileProcessor::GetInstance();
		/**/

		Mutex mux(false, "PlayerMux");

		vector<SmartPointer<GameObject>> objToAdd;

		vector<SmartPointer<GameObject>> objInScene;

		PhysicsInfo * physicsP = new PhysicsInfo(5.0f, 0.5f);
		PhysicsInfo * physicsPP = new PhysicsInfo(10.0f, 0.5f);

		physicsP->SetGameObject(pp);
		physicsPP->SetGameObject(goombaLists[0]);

		ReferenceCounter* refC = new ReferenceCounter();
		SmartPointer<GameObject> smart(SmartPointer<GameObject>(pp, refC));

		PhysicsInfo* info = new PhysicsInfo(10.0f, 0.5f, smart);
		info->SetGameObject(pp);

		Processor.AddToLoadQueue(*new ShowTask("Externals\\Data\\Player.lua", physicsP, objToAdd, mux));

		bool bQuit = false;

		//pp->SetPosition(Point2D(0.0f, -300.0f));
		physicsP->GetGameObject()->SetPosition(Point2D(0.0f, -300.0f));
		//goombaLists[0]->SetPosition(Point2D(400.0f, -100.0f));
		goodG->SetBoundingBoxCenter(Vector3D(0.0f, goodG->GetSize().GetY() / 2, 0.0f));

		goodG->SetVelocity(Vector3D(physicsP->GetGameObject()->GetVelocity(), 0.0f));
		goomba->SetBoundingBoxCenter(Vector3D(0.0f, goomba->GetSize().GetY() / 2, 0.0f));

		do
		{
			t->GetCounter();
			t->GetFrequency();
			t->CalculateFrameTimeInMS();
			dt = t->GetLastFrameTimeInMS();
			// We need to let GLib do it's thing. 
			GLib::Service(bQuit);

			if (!bQuit)
			{
				// Tell GLib that we want to start rendering
				GLib::BeginRendering();
				// Tell GLib that we want to render some sprites
				GLib::Sprites::BeginRendering();

				if (goodG)
				{
					//info->SetGameObject(pp);

					Point2D force = Point2D(forceV, 0.0f);

					if (in->IsDown('A'))
					{
						force += Point2D(-2 * forceV, 0.0f);
						goodG->SetVelocity(Vector3D(force.GetX(), force.GetY(), 0.0f));
					}
					if (in->IsDown('D'))
					{
						force += Point2D(0.0f, 0.0f);
						goodG->SetVelocity(Vector3D(force.GetX(), force.GetY(), 0.0f));
					}
					if (in->IsDown('S'))
					{
						force += Point2D(0.0f, -1 * forceV);
						goodG->SetVelocity(Vector3D(force.GetX(), force.GetY(), 0.0f));
					}
					if (in->IsDown('W'))
					{
						force += Point2D(0.0f, forceV);
						goodG->SetVelocity(Vector3D(force.GetX(), force.GetY(), 0.0f));
					}

					if (in->IsDown('Q'))
					{
						bQuit = true;
					}

					MoveToAddList(objToAdd, objInScene, mux);

					UpdatePhysicsIndividual(physicsP, force, dt);

					//physicsP->Update(Point2D(goodG->GetVelocity().GetX(), goodG->GetVelocity().GetY()), dt);

					GLib::Point2D	Offset = { physicsP->GetGameObject()->GetPositionX(), physicsP->GetGameObject()->GetPositionY() };

					// Tell GLib to render this sprite at our calculated location, last value is rotation degree.
					GLib::Sprites::RenderSprite(*(goodG->GetImage()), Offset, 0.0f);
				}

				if (goombaLists[0] && goomba)
				{
					physicsPP->SetGameObject(goombaLists[0]);
					//physicsP->GetGameObject()->SetVelocity(Point2D(5.0f, 0.0f));
					//goomba->SetVelocity(Vector3D(5.0f, 0.0f, 0.0f));
					//goombaLists[0]->SetVelocity(Point2D(5.0f, 0.0f));

					if (AreAboutEqual(forceV, 0.0f, 0.001f))
						bQuit = true;
					
					physicsPP->Update(Point2D(goomba->GetVelocity().GetX(), goomba->GetVelocity().GetY()), dt);

					float colTime;
					Vector3D colNormal;

					if (checker->isColliding(goodG, goomba, physicsP, physicsPP, dt, colTime, colNormal))
					{
						// collision check
						//checker->ResolveCollision(goodG, goomba, physicsP, physicsPP, colNormal, true, false);

						forceV -= 0.1f;
						goombaLists[0]->SetPosition(locations[rand() % locationSize]);
					}

					GLib::Point2D	Offset = { physicsPP->GetGameObject()->GetPositionX(), physicsPP->GetGameObject()->GetPositionY() };

					// Tell GLib to render this sprite at our calculated location, last value is rotation degree.
					GLib::Sprites::RenderSprite(*(goomba->GetImage()), Offset, 0.0f);
				}

				// Tell GLib we're done rendering sprites
				GLib::Sprites::EndRendering();
				// Tell GLib we're done rendering
				GLib::EndRendering();
			}
		} while (bQuit == false);

		/**/
		Azra::ThreadedFileProcessor::Shutdown();
		/**/

		//if (pGoodGuy)
		//	GLib::Sprites::Release(pGoodGuy);
		//if (pBadGuy)
		//	GLib::Sprites::Release(pBadGuy);
		//if (pGoomba)
		//	GLib::Sprites::Release(pGoomba);

		delete goodG;
		delete goomba;

		GLib::Shutdown();
	}

	CloseEngine();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG

	return 0;

}


//int RespawnMonster(Monster list[])
//{
//	const unsigned int max = 10;
//	bool isSuccessful = false;
//	for (int i = 0; i < max; i++)
//	{
//		// if there is a spot to respawn monster
//		if (list[i].GetStatus() == "dead")
//		{
//			// make it alive (aka respawn) and assign random health and location to it
//			list[i].Activate();
//			list[i].ResetHealth();
//			list[i].ResetPosition();
//			isSuccessful = true;
//			return i;
//			break;
//		}
//	}
//
//	if (!isSuccessful)
//		printf_s("Monster List is currently full, cannot spawn more monsters!\n");
//	return -1;
//}

void SmartWeakPointerTest()
{
	// Unit Test
	ReferenceCounter* ref = new ReferenceCounter();
	SmartPointer<GameObject> sm(new GameObject(), ref);
	SmartPointer<GameObject> stupid(sm);
	SmartPointer<GameObject> superStupid(move(stupid)); // stupid became NULL after moving it to superStupid
	SmartPointer<GameObject> thisisstupid = sm;

	WeakPointer<GameObject> wk(sm);
	WeakPointer<GameObject> wk2(wk);
	WeakPointer<GameObject> wk3(move(wk));

	SmartPointer<GameObject> sth = wk2.AcquireSmart();

	assert(sth == sm);

	//delete ref;
	//ref = NULL;
}

void MoveToAddList(vector<SmartPointer<GameObject>> & loadQ, vector<SmartPointer<GameObject>> & addQ, Mutex & mutex)
{
	mutex.Acquire();
	if (loadQ.size() > 0)
	{
		SmartPointer<GameObject> temp = loadQ.back();
		loadQ.pop_back();
		addQ.push_back(temp);
	}
	mutex.Release();
}

void UpdatePhysics(vector<PhysicsInfo *> pInfoList, Point2D force, float dt)
{
	if (pInfoList.size() > 0)
	{
		for (size_t i = 0; i < pInfoList.size(); i++)
		{
			pInfoList[i]->Update(force, dt);
		}
	}
}

void UpdatePhysicsIndividual(PhysicsInfo * pInfo, Point2D force, float dt)
{
	pInfo->Update(force, dt);
}

void UpdateBoundingBoxIndividual(Sprite * image)
{
	image->SetBoundingBoxCenter(Vector3D(0.0f, image->GetBoundingBox().extent.GetY(), 0.0f));
}

int RespawnMonsterP(Monster* list[], MonsterController* monController)
{
	const unsigned int max = 10;
	bool isSuccessful = false;
	for (int i = 0; i < max; i++)
	{
		if (list[i]->GetStatus() == "dead")
		{
			delete list[i];
			list[i] = new Monster();
			monController->SetGameObject(list[i]);
			monController->SetGameObjectPosition();
			isSuccessful = true;
			return i;
			break;
		}
	}

	if (!isSuccessful)
		printf_s("Monster List is currently full, cannot spawn more monsters!\n");
	return -1;
}

int RespawnGoombaP(Goomba* list[], GoombaController* gooController)
{
	const unsigned int max = 5;
	bool isSuccessful = false;
	for (int i = 0; i < max; i++)
	{
		if (list[i]->GetStatus() == "dead")
		{
			delete list[i];
			list[i] = new Goomba();
			gooController->SetGameObject(list[i]);
			gooController->SetGameObjectPosition();
			isSuccessful = true;
			return i;
			break;
		}
	}

	if (!isSuccessful)
		printf_s("Goomba List is currently full, cannot spawn more Goombas!\n");
	return -1;
}

float GetRadianFromDegree(float degree)
{
	return static_cast<float>(degree * M_PI / 180);
}