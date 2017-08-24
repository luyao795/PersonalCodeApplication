// Inline function definitions for GameObject class

namespace Engine
{

	inline Point2D GameObject::GetPosition() const
	{
		return position;
	}

	inline Point2D GameObject::GetVelocity() const
	{
		return velocity;
	}

	inline float GameObject::GetPositionX() const
	{
		return xPos;
	}

	inline float GameObject::GetPositionY() const
	{
		return yPos;
	}

	inline void GameObject::SetPosition(Point2D& targetPos)
	{
		position = targetPos;
		xPos = targetPos.GetX();
		yPos = targetPos.GetY();
	}

	inline void GameObject::SetVelocity(Point2D& targetVel)
	{
		velocity = targetVel;
	}

	inline void GameObject::SetPosition(float x, float y)
	{
		xPos = x;
		yPos = y;
		position = Point2D(x, y);
	}

	inline void GameObject::SetVelocity(float x, float y)
	{
		velocity = Point2D(x, y);
	}

	inline void GameObject::SetPositionX(float x)
	{
		xPos = x;
	}

	inline void GameObject::SetPositionY(float y)
	{
		yPos = y;
	}

}