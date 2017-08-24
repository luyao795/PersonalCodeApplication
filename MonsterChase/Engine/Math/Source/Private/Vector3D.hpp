// Inline function definitions for Vector3D class

#include <math.h>

namespace Engine
{
	inline float Vector3D::GetX() const
	{
		return xPos;
	}

	inline float Vector3D::GetY() const
	{
		return yPos;
	}

	inline float Vector3D::GetZ() const
	{
		return zPos;
	}

	inline void Vector3D::SetX(const float x)
	{
		xPos = x;
	}

	inline void Vector3D::SetY(const float y)
	{
		yPos = y;
	}

	inline void Vector3D::SetZ(const float z)
	{
		zPos = z;
	}

	inline void Vector3D::MoveX(const float xDis)
	{
		xPos += xDis;
	}

	inline void Vector3D::MoveY(const float yDis)
	{
		yPos += yDis;
	}

	inline void Vector3D::MoveZ(const float zDis)
	{
		zPos += zDis;
	}

	inline bool Vector3D::isZero()
	{
		return (xPos == 0.0f && yPos == 0.0f && zPos == 0.0f);
	}

	inline float Vector3D::GetLength() const
	{
		return sqrtf(xPos * xPos + yPos * yPos + zPos * zPos);
	}

	inline void Vector3D::operator=(const Vector3D &other)
	{
		xPos = other.GetX();
		yPos = other.GetY();
		zPos = other.GetZ();
	}

	inline bool Vector3D::operator==(const Vector3D &other)
	{
		return (xPos == other.GetX() && yPos == other.GetY() && zPos == other.GetZ());
	}

	inline bool Vector3D::operator!=(const Vector3D &other)
	{
		return (xPos != other.GetX() || yPos != other.GetY() || zPos != other.GetZ());
	}

	inline Vector3D Vector3D::operator+=(const Vector3D &other)
	{
		xPos += other.GetX();
		yPos += other.GetY();
		zPos += other.GetZ();
		return *this;
	}

	inline Vector3D Vector3D::operator-=(const Vector3D &other)
	{
		xPos -= other.GetX();
		yPos -= other.GetY();
		zPos -= other.GetZ();
		return *this;
	}

	inline Vector3D Vector3D::operator*=(const float scale)
	{
		xPos *= scale;
		yPos *= scale;
		zPos *= scale;
		return *this;
	}

	inline Vector3D Vector3D::operator/=(const float scale)
	{
		xPos /= scale;
		yPos /= scale;
		zPos /= scale;
		return *this;
	}

	inline Vector3D operator+(const Vector3D &left, const Vector3D &right)
	{
		return Vector3D(left.GetX() + right.GetX(), left.GetY() + right.GetY(), left.GetZ() + right.GetZ());
	}

	inline Vector3D operator-(const Vector3D &left, const Vector3D &right)
	{
		return Vector3D(left.GetX() - right.GetX(), left.GetY() - right.GetY(), left.GetZ() - right.GetZ());
	}

	inline Vector3D operator*(const Vector3D &target, const float scale)
	{
		return Vector3D(target.GetX() * scale, target.GetY() * scale, target.GetZ() * scale);
	}

	inline Vector3D operator/(const Vector3D &target, const float scale)
	{
		return Vector3D(target.GetX() / scale, target.GetY() / scale, target.GetZ() / scale);
	}
}