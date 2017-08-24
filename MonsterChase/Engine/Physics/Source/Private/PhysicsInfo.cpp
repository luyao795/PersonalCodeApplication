#include "SmartPointer.h"
//#include "WeakPointer.h"
#include "GameObject.h"
//#include "Point2D.h"
#include "GLib.h"
#include "PhysicsInfo.h"

using namespace std;

namespace Engine
{
	PhysicsInfo::PhysicsInfo(float defaultMass, float defaultDrag) :
		mass(defaultMass), drag(defaultDrag), gameObject(SmartPointer<GameObject>(NULL))
	{
	}

	PhysicsInfo::PhysicsInfo(float defaultMass, float defaultDrag, SmartPointer<GameObject> smart) :
		mass(defaultMass), drag(defaultDrag), gameObject(smart)
	{
	}

	PhysicsInfo::~PhysicsInfo()
	{
		if (gameObject.GetGameObject())
		{
			gameObject.Dereference();
		}
		gameObject.ReleaseReference();
	}

	void PhysicsInfo::Update(Point2D force, float dt)
	{
		Point2D acceleration = force / mass;
		Point2D prevVel = gameObject->GetVelocity();
		Point2D velocity = gameObject->GetVelocity() + acceleration * dt;
		Point2D friction = velocity * drag * (-1.0f);

		gameObject->SetVelocity(velocity.isZero() ? velocity : velocity + friction);
		gameObject->SetPosition(gameObject->GetPosition() + (gameObject->GetVelocity() + prevVel) / 2.0f * dt);
	}

	void PhysicsInfo::SetGameObject(GameObject * object)
	{
		if (object)
			gameObject.SetGameObject(object);
	}

	void PhysicsInfo::SetGameObjectSMPTR(SmartPointer<GameObject> * object)
	{
		if (object->GetGameObject())
			gameObject.SetGameObject(object->GetGameObject());
	}

	GameObject * PhysicsInfo::GetGameObject()
	{
		return gameObject.GetGameObject();
	}

	SmartPointer<GameObject> PhysicsInfo::GetSmartPointer()
	{
		return gameObject;
	}

	void PhysicsInfo::SetMass(float newMass)
	{
		mass = newMass;
	}

	float PhysicsInfo::GetMass()
	{
		return mass;
	}

	void PhysicsInfo::SetDrag(float newDrag)
	{
		drag = newDrag;
	}

	float PhysicsInfo::GetDrag()
	{
		return drag;
	}
}