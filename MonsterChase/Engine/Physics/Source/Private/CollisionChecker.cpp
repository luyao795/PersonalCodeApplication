#define _USE_MATH_DEFINES
#include <cmath>
#include "DebugPrint.h"
#include "MessagingSystem.h"
#include "Vector4D.h"
#include "Matrix4X4.h"
#include "Sprite.h"
#include "PhysicsInfo.h"
#include "Timer.h"
#include "Accumulator.h"
#include "ValidityErrorChecker.h"
#include "CollisionChecker.h"

using namespace std;

namespace Engine
{
	CollisionChecker::CollisionChecker()
	{
	}

	bool CollisionChecker::isColliding(Sprite * first, Sprite * second, PhysicsInfo * pInfoFirst, PhysicsInfo * pInfoSecond, float deltaTime, float & collisionTime, Vector3D & collisionNormal)
	{
		static Accumulator acc("isColliding");
		double start = Timer::GetCounterStatic();

		bool isSeparate = false;

		float tFrame = deltaTime;

		Matrix4X4 firstRotation = mat.GetRotationMatrix(GetRadianFromDegree(first->GetRotation()));
		Matrix4X4 firstTranslationCol = mat.GetColVectorTranslationMatrix(Vector4D(pInfoFirst->GetGameObject()->GetPositionX(), pInfoFirst->GetGameObject()->GetPositionY(), 0.0f, 0.0f));

		Matrix4X4 firstToWorld = firstTranslationCol * firstRotation;
		Matrix4X4 worldToFirst = firstToWorld.Inverse();

		Matrix4X4 secondRotation = mat.GetRotationMatrix(GetRadianFromDegree(second->GetRotation()));
		Matrix4X4 secondTranslationCol = mat.GetColVectorTranslationMatrix(Vector4D(pInfoSecond->GetGameObject()->GetPositionX(), pInfoSecond->GetGameObject()->GetPositionY(), 0.0f, 0.0f));

		Matrix4X4 secondToWorld = secondTranslationCol * secondRotation;
		Matrix4X4 worldToSecond = secondToWorld.Inverse();

		Matrix4X4 firstToSecond = worldToSecond * firstToWorld;
		Matrix4X4 secondToFirst = worldToFirst * secondToWorld;

		Vector3D VelFirstRelToSecond = Vector3D(pInfoFirst->GetGameObject()->GetVelocity() - pInfoSecond->GetGameObject()->GetVelocity(), 0.0f);
		Vector4D VelFirstInSecond = worldToSecond.MultiplyRightVector(Vector4D(VelFirstRelToSecond, 0.0f));

		Vector3D VelSecondRelToFirst = Vector3D(pInfoSecond->GetGameObject()->GetVelocity() - pInfoFirst->GetGameObject()->GetVelocity(), 0.0f);
		Vector4D VelSecondInFirst = worldToFirst.MultiplyRightVector(Vector4D(VelSecondRelToFirst, 0.0f));

		Vector4D firstBBCenterInWorld = firstToWorld.MultiplyRightVector(Vector4D(first->GetBoundingBox().center, 1.0f));
		Vector4D firstBBCenterInSecond = worldToSecond.MultiplyRightVector(firstBBCenterInWorld);

		Vector4D secondBBCenterInWorld = secondToWorld.MultiplyRightVector(Vector4D(second->GetBoundingBox().center, 1.0f));
		Vector4D secondBBCenterInFirst = worldToFirst.MultiplyRightVector(secondBBCenterInWorld);

		float centerDistFirstInSecondX = fabs(firstBBCenterInSecond.GetX() - second->GetBoundingBox().center.GetX());
		float centerDistFirstInSecondY = fabs(firstBBCenterInSecond.GetY() - second->GetBoundingBox().center.GetY());

		float centerDistSecondInFirstX = fabs(secondBBCenterInFirst.GetX() - first->GetBoundingBox().center.GetX());
		float centerDistSecondInFirstY = fabs(secondBBCenterInFirst.GetY() - first->GetBoundingBox().center.GetY());

		Vector4D firstExtentXInSecond = firstToSecond.MultiplyRightVector(Vector4D(first->GetBoundingBox().extent.GetX(), 0.0f, 0.0f, 0.0f));
		Vector4D firstExtentYInSecond = firstToSecond.MultiplyRightVector(Vector4D(0.0f, first->GetBoundingBox().extent.GetY(), 0.0f, 0.0f));

		Vector4D secondExtentXInFirst = secondToFirst.MultiplyRightVector(Vector4D(second->GetBoundingBox().extent.GetX(), 0.0f, 0.0f, 0.0f));
		Vector4D secondExtentYInFirst = secondToFirst.MultiplyRightVector(Vector4D(0.0f, second->GetBoundingBox().extent.GetY(), 0.0f, 0.0f));

		float firstProjectionXOnSecond = fabs(firstExtentXInSecond.GetX()) + fabs(firstExtentYInSecond.GetX());
		float firstProjectionYOnSecond = fabs(firstExtentXInSecond.GetY()) + fabs(firstExtentYInSecond.GetY());

		float secondProjectionXOnFirst = fabs(secondExtentXInFirst.GetX()) + fabs(secondExtentYInFirst.GetX());
		float secondProjectionYOnFirst = fabs(secondExtentXInFirst.GetY()) + fabs(secondExtentYInFirst.GetY());

		float DistanceFirstSecondXClose = 0.0f;
		float DistanceFirstSecondXOpen = 0.0f;
		float tCloseXFirstInSecond = 0.0f;

		float DistanceFirstSecondYClose = 0.0f;
		float DistanceFirstSecondYOpen = 0.0f;
		float tCloseYFirstInSecond = 0.0f;

		float DistanceSecondFirstXClose = 0.0f;
		float DistanceSecondFirstXOpen = 0.0f;
		float tCloseXSecondInFirst = 0.0f;

		float DistanceSecondFirstYClose = 0.0f;
		float DistanceSecondFirstYOpen = 0.0f;
		float tClostYSecondInFirst = 0.0f;

		float tOpenXFirstInSecond = 0.0f;
		float tOpenYFirstInSecond = 0.0f;

		float tOpenXSecondInFirst = 0.0f;
		float tOpenYSecondInFirst = 0.0f;

		float firstExtentX = first->GetBoundingBox().extent.GetX() + secondProjectionXOnFirst;
		float secondExtentX = second->GetBoundingBox().extent.GetX() + firstProjectionXOnSecond;

		float firstExtentY = first->GetBoundingBox().extent.GetY() + secondProjectionYOnFirst;
		float secondExtentY = second->GetBoundingBox().extent.GetY() + firstProjectionYOnSecond;

		float firstLeftEdge = first->GetBoundingBox().center.GetX() - firstExtentX;
		float firstRightEdge = first->GetBoundingBox().center.GetX() + firstExtentX;
		float firstTopEdge = first->GetBoundingBox().center.GetY() + firstExtentY;
		float firstBottomEdge = first->GetBoundingBox().center.GetY() - firstExtentY;

		float secondLeftEdge = second->GetBoundingBox().center.GetX() - secondExtentX;
		float secondRightEdge = second->GetBoundingBox().center.GetX() + secondExtentX;
		float secondTopEdge = second->GetBoundingBox().center.GetY() + secondExtentY;
		float secondBottomEdge = second->GetBoundingBox().center.GetY() - secondExtentY;

		if (!isSeparate)
		{
			// Check 1 out of 4.
			if (AreAboutEqual(VelFirstInSecond.GetX(), 0.0f))
			{
				if (firstBBCenterInSecond.GetX() < secondLeftEdge || firstBBCenterInSecond.GetX() > secondRightEdge)
					isSeparate = true;
			}
			else
			{
				Vector4D secondXWorld = secondToWorld.MultiplyRightVector(Vector4D(1.0f, 0.0f, 0.0f, 0.0f));
				float secondExtentX = second->GetBoundingBox().extent.GetX() + firstProjectionXOnSecond;
				float secondLeftX = second->GetBoundingBox().center.GetX() - secondExtentX;
				DistanceFirstSecondXClose = secondLeftX - firstBBCenterInSecond.GetX();
				tCloseXFirstInSecond = DistanceFirstSecondXClose / VelFirstInSecond.GetX();
				float secondRightX = second->GetBoundingBox().center.GetX() + secondExtentX;
				DistanceFirstSecondXOpen = secondRightX - firstBBCenterInSecond.GetX();
				tOpenXFirstInSecond = DistanceFirstSecondXOpen / VelFirstInSecond.GetX();

				if (tOpenXFirstInSecond < tCloseXFirstInSecond)
				{
					float temp = tOpenXFirstInSecond;
					tOpenXFirstInSecond = tCloseXFirstInSecond;
					tCloseXFirstInSecond = temp;
				}
				collisionNormal = Vector3D(secondXWorld.GetX(), secondXWorld.GetY(), secondXWorld.GetZ());
				collisionNormal = collisionNormal.Normalize();
			}

			// Check 2 out of 4.
			if (AreAboutEqual(VelFirstInSecond.GetY(), 0.0f))
			{
				if (firstBBCenterInSecond.GetY() < secondBottomEdge || firstBBCenterInSecond.GetY() > secondTopEdge)
					isSeparate = true;
			}
			else
			{
				Vector4D secondYWorld = secondToWorld.MultiplyRightVector(Vector4D(0.0f, 1.0f, 0.0f, 0.0f));
				float secondExtentY = second->GetBoundingBox().extent.GetY() + firstProjectionYOnSecond;
				float secondLeftY = second->GetBoundingBox().center.GetY() - secondExtentY;
				DistanceFirstSecondYClose = secondLeftY - firstBBCenterInSecond.GetY();
				tCloseYFirstInSecond = DistanceFirstSecondYClose / VelFirstInSecond.GetY();
				float secondRightY = second->GetBoundingBox().center.GetY() + secondExtentY;
				DistanceFirstSecondYOpen = secondRightY - firstBBCenterInSecond.GetY();
				tOpenYFirstInSecond = DistanceFirstSecondYOpen / VelFirstInSecond.GetY();

				if (tOpenYFirstInSecond < tCloseYFirstInSecond)
				{
					float temp = tOpenYFirstInSecond;
					tOpenYFirstInSecond = tCloseYFirstInSecond;
					tCloseYFirstInSecond = temp;
				}
				collisionNormal = Vector3D(secondYWorld.GetX(), secondYWorld.GetY(), secondYWorld.GetZ());
				collisionNormal = collisionNormal.Normalize();
			}

			// Check 3 out of 4.
			if (AreAboutEqual(VelSecondInFirst.GetX(), 0.0f))
			{
				if (secondBBCenterInFirst.GetX() < firstLeftEdge || secondBBCenterInFirst.GetX() > firstRightEdge)
					isSeparate = true;
			}
			else
			{
				Vector4D firstXWorld = firstToWorld.MultiplyRightVector(Vector4D(1.0f, 0.0f, 0.0f, 0.0f));
				float firstExtentX = first->GetBoundingBox().extent.GetX() + secondProjectionXOnFirst;
				float firstLeftX = first->GetBoundingBox().center.GetX() - firstExtentX;
				DistanceSecondFirstXClose = firstLeftX - secondBBCenterInFirst.GetX();
				tCloseXSecondInFirst = DistanceSecondFirstXClose / VelSecondInFirst.GetX();
				float firstRightX = first->GetBoundingBox().center.GetX() + firstExtentX;
				DistanceFirstSecondXOpen = firstRightX - secondBBCenterInFirst.GetX();
				tOpenXSecondInFirst = DistanceFirstSecondXOpen / VelSecondInFirst.GetX();

				if (tOpenXSecondInFirst < tCloseXSecondInFirst)
				{
					float temp = tOpenXSecondInFirst;
					tOpenXSecondInFirst = tCloseXSecondInFirst;
					tCloseXSecondInFirst = temp;
				}
				collisionNormal = Vector3D(firstXWorld.GetX(), firstXWorld.GetY(), firstXWorld.GetZ());
				collisionNormal = collisionNormal.Normalize();
			}

			// Check 4 out of 4.
			if (AreAboutEqual(VelSecondInFirst.GetY(), 0.0f))
			{
				if (secondBBCenterInFirst.GetY() < firstBottomEdge || secondBBCenterInFirst.GetY() > firstTopEdge)
					isSeparate = true;
			}
			else
			{
				Vector4D firstYWorld = firstToWorld.MultiplyRightVector(Vector4D(0.0f, 1.0f, 0.0f, 0.0f));
				float firstExtentY = first->GetBoundingBox().extent.GetY() + secondProjectionYOnFirst;
				float firstLeftY = first->GetBoundingBox().center.GetY() - firstExtentY;
				DistanceSecondFirstYClose = firstLeftY - secondBBCenterInFirst.GetY();
				tClostYSecondInFirst = DistanceSecondFirstYClose / VelSecondInFirst.GetY();
				float firstRightY = first->GetBoundingBox().center.GetY() + firstExtentY;
				DistanceFirstSecondYOpen = firstRightY - secondBBCenterInFirst.GetY();
				tOpenYSecondInFirst = DistanceFirstSecondYOpen / VelSecondInFirst.GetY();

				if (tOpenYSecondInFirst < tClostYSecondInFirst)
				{
					float temp = tOpenYSecondInFirst;
					tOpenYSecondInFirst = tClostYSecondInFirst;
					tClostYSecondInFirst = temp;
				}
				collisionNormal = Vector3D(firstYWorld.GetX(), firstYWorld.GetY(), firstYWorld.GetZ());
				collisionNormal = collisionNormal.Normalize();
			}
		}

		if (!isSeparate)
		{
			float tOpenMin = tOpenXFirstInSecond;

			if (tOpenXSecondInFirst < tOpenMin)
				tOpenMin = tOpenXSecondInFirst;

			if (tOpenYFirstInSecond < tOpenMin)
				tOpenMin = tOpenYFirstInSecond;

			if (tOpenYSecondInFirst < tOpenMin)
				tOpenMin = tOpenYSecondInFirst;

			float tCloseMax = tCloseXFirstInSecond;

			if (tCloseXSecondInFirst > tCloseMax)
			{
				tCloseMax = tCloseXSecondInFirst;
			}

			if (tCloseYFirstInSecond > tCloseMax)
			{
				tCloseMax = tCloseYFirstInSecond;
			}

			if (tClostYSecondInFirst > tCloseMax)
			{
				tCloseMax = tClostYSecondInFirst;
			}

			if (tCloseMax > tFrame || tOpenMin < 0.0f)
				isSeparate = true;
			else
			{
				if (tCloseMax > tOpenMin)
					isSeparate = true;
				else
					isSeparate = false;
			}
			collisionTime = tCloseMax;
		}

		acc += static_cast<float>(Timer::GetDiff(start, Timer::GetCounterStatic()));

		return !isSeparate;
	}

	void CollisionChecker::ResolveCollision(Sprite * first, Sprite * second, PhysicsInfo * pInfoFirst, PhysicsInfo * pInfoSecond, Vector3D& collisionNormal, bool firstControlledByPlayer, bool secondControlledByPlayer)
	{
		MessagingSystem msgSys = MessagingSystem();
		msgSys.AddMessageHandler("Collision", std::bind(&CollisionChecker::HandleCollisionMessage, this, std::placeholders::_1), Message::COLLISION);

		float m1 = pInfoFirst->GetMass();
		float m2 = pInfoSecond->GetMass();

		Vector3D vg1 = Vector3D(pInfoFirst->GetGameObject()->GetVelocity(), 0.0f);
		Vector3D vg2 = Vector3D(pInfoSecond->GetGameObject()->GetVelocity(), 0.0f);

		//Vector3D v1 = first->GetVelocity();
		//Vector3D v2 = second->GetVelocity();

		// Conservation of Momentum
		//Vector3D v1pm = v1 * ((m1 - m2) / (m1 + m2)) + v2 * ((2 * m2) / (m1 + m2));
		//Vector3D v2pm = v1 * ((2 * m1) / (m1 + m2)) - v2 * ((m1 - m2) / (m1 + m2));

		Vector3D vg1pm = vg1 * ((m1 - m2) / (m1 + m2)) + vg2 * ((2 * m2) / (m1 + m2));
		Vector3D vg2pm = vg1 * ((2 * m1) / (m1 + m2)) + vg2 * ((m2 - m1) / (m1 + m2));

		// Reflection
		//Vector3D v1pr = v1 - collisionNormal * (2 * (v1.Dot(collisionNormal)));
		//Vector3D v2pr = v2 - collisionNormal * (2 * (v2.Dot(collisionNormal)));

		Vector3D vg1pr = vg1 - (collisionNormal * (2 * (vg1.Dot(collisionNormal))));
		Vector3D vg2pr = vg2 - (collisionNormal * (2 * (vg2.Dot(collisionNormal))));

		//Vector3D v1p = v1pm + v1pr;
		//Vector3D v2p = v2pm + v2pr;

		Vector3D vg1p = vg1pm + vg1pr;
		Vector3D vg2p = vg2pm + vg2pr;

		first->SetVelocity(vg1p);
		pInfoFirst->GetGameObject()->SetVelocity(Point2D(vg1p.GetX(), vg1p.GetY()));

		second->SetVelocity(vg2p);
		pInfoSecond->GetGameObject()->SetVelocity(Point2D(vg2p.GetX(), vg2p.GetY()));
	}

	float CollisionChecker::GetRadianFromDegree(float degree)
	{
		return static_cast<float>(degree * M_PI / 180.0f);
	}

	void CollisionChecker::HandleCollisionMessage(const HashedString & msg)
	{
		OutputDebugStringA(msg.GetString());
	}
}