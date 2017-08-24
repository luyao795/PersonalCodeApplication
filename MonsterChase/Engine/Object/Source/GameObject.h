#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Point2D.h"

namespace Engine
{

	class GameObject
	{
	public:
		GameObject() :
			xPos(0.0f),
			yPos(0.0f),
			position(Point2D(0.0f, 0.0f)),
			velocity(Point2D(0.0f, 0.0f))
		{
		}

		GameObject(Point2D& pos) :
			xPos(pos.GetX()),
			yPos(pos.GetY()),
			position(pos),
			velocity(Point2D(0.0f, 0.0f))
		{
		}

		GameObject(float x, float y) :
			xPos(x),
			yPos(y),
			position(Point2D(x, y)),
			velocity(Point2D(0.0f, 0.0f))
		{
		}

		~GameObject()
		{
		}

		inline Point2D GetPosition() const;
		inline Point2D GetVelocity() const;
		inline float GetPositionX() const;
		inline float GetPositionY() const;
		inline void SetPosition(Point2D& targetPos);
		inline void SetPosition(float x, float y);
		inline void SetPositionX(float x);
		inline void SetPositionY(float y);
		inline void SetVelocity(Point2D& targetVel);
		inline void SetVelocity(float x, float y);

	private:
		float xPos;
		float yPos;
		Point2D position;
		Point2D velocity;
	};
}
#include "GameObject.hpp"
#endif // GAMEOBJECT_H

