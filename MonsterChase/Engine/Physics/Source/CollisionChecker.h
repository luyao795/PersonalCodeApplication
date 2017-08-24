#ifndef COLLISIONCHECKER_H
#define COLLISIONCHECKER_H

#include "Sprite.h"
#include "HashedString.h"

namespace Engine
{
	class CollisionChecker
	{
	public:
		CollisionChecker();
		bool isColliding(Sprite * first, Sprite * second, PhysicsInfo * pInfoFirst, PhysicsInfo * pInfoSecond, float deltaTime, float & collisionTime, Vector3D & collisionNormal);
		void ResolveCollision(Sprite * first, Sprite * second, PhysicsInfo * pInfoFirst, PhysicsInfo * pInfoSecond, Vector3D& collisionNormal, bool firstControlledByPlayer, bool secondControlledByPlayer);
		float GetRadianFromDegree(float degree);
		void HandleCollisionMessage(const HashedString & msg);
	private:
		Matrix4X4 mat;
	};
}

#endif // !COLLISIONCHECKER_H
