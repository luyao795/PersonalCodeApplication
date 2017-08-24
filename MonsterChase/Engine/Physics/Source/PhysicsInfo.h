#ifndef PHYSICSINFO_H
#define PHYSICSINFO_H

#include "GameObject.h"
#include "SmartPointer.h"
//#include "WeakPointer.h"

namespace Engine
{
	class PhysicsInfo
	{
	public:
		PhysicsInfo(float defaultMass, float defaultDrag);
		PhysicsInfo(float defaultMass, float defaultDrag, SmartPointer<GameObject> smart);
		~PhysicsInfo();
		void Update(Point2D force, float dt);
		void SetGameObject(GameObject * object);
		void SetGameObjectSMPTR(SmartPointer<GameObject> * object);
		GameObject* GetGameObject();
		SmartPointer<GameObject> GetSmartPointer();
		void SetMass(float newMass);
		float GetMass();
		void SetDrag(float newDrag);
		float GetDrag();
	private:
		SmartPointer<GameObject> gameObject;
		float mass;
		// coefficient for friction force
		float drag;
	};
}

#endif // !PHYSICSINFO_H
