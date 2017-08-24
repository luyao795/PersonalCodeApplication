// Inline function definitions for Vector4D class

#include <math.h>

namespace Engine
{
	inline float Vector4D::GetX() const
	{
		return xPos;
	}

	inline float Vector4D::GetY() const
	{
		return yPos;
	}

	inline float Vector4D::GetZ() const
	{
		return zPos;
	}

	inline float Vector4D::GetU() const
	{
		return uPos;
	}

	inline void Vector4D::SetX(const float x)
	{
		xPos = x;
	}

	inline void Vector4D::SetY(const float y)
	{
		yPos = y;
	}

	inline void Vector4D::SetZ(const float z)
	{
		zPos = z;
	}

	inline void Vector4D::SetU(const float u)
	{
		uPos = u;
	}

	inline void Vector4D::MoveX(const float xDis)
	{
		xPos += xDis;
	}

	inline void Vector4D::MoveY(const float yDis)
	{
		yPos += yDis;
	}

	inline void Vector4D::MoveZ(const float zDis)
	{
		zPos += zDis;
	}

	inline void Vector4D::MoveU(const float uDis)
	{
		uPos += uDis;
	}

	inline bool Vector4D::isZero()
	{
		return (xPos == 0.0f && yPos == 0.0f && zPos == 0.0f && uPos == 0.0f);
	}

	inline float Vector4D::GetLength() const
	{
		return sqrtf(xPos * xPos + yPos * yPos + zPos * zPos + uPos * uPos);
	}

	inline void Vector4D::operator=(const Vector4D &other)
	{
		xPos = other.GetX();
		yPos = other.GetY();
		zPos = other.GetZ();
		uPos = other.GetU();
	}

	inline bool Vector4D::operator==(const Vector4D &other)
	{
		return (xPos == other.GetX() && yPos == other.GetY() && zPos == other.GetZ() && uPos == other.GetU());
	}

	inline bool Vector4D::operator!=(const Vector4D &other)
	{
		return (xPos != other.GetX() || yPos != other.GetY() || zPos != other.GetZ() || uPos != other.GetU());
	}

	inline Vector4D Vector4D::operator+=(const Vector4D &other)
	{
		xPos += other.GetX();
		yPos += other.GetY();
		zPos += other.GetZ();
		uPos += other.GetU();
		return *this;
	}

	inline Vector4D Vector4D::operator-=(const Vector4D &other)
	{
		xPos -= other.GetX();
		yPos -= other.GetY();
		zPos -= other.GetZ();
		uPos -= other.GetU();
		return *this;
	}

	inline Vector4D Vector4D::operator*=(const float scale)
	{
		xPos *= scale;
		yPos *= scale;
		zPos *= scale;
		uPos *= scale;
		return *this;
	}

	inline Vector4D Vector4D::operator/=(const float scale)
	{
		xPos /= scale;
		yPos /= scale;
		zPos /= scale;
		uPos /= scale;
		return *this;
	}

	inline Vector4D operator+(const Vector4D &left, const Vector4D &right)
	{
		return Vector4D(left.GetX() + right.GetX(), left.GetY() + right.GetY(), left.GetZ() + right.GetZ(), left.GetU() + right.GetU());
	}

	inline Vector4D operator-(const Vector4D &left, const Vector4D &right)
	{
		return Vector4D(left.GetX() - right.GetX(), left.GetY() - right.GetY(), left.GetZ() - right.GetZ(), left.GetU() - right.GetU());
	}

	inline Vector4D operator*(const Vector4D &target, const float scale)
	{
		return Vector4D(target.GetX() * scale, target.GetY() * scale, target.GetZ() * scale, target.GetU() * scale);
	}

	inline Vector4D operator/(const Vector4D &target, const float scale)
	{
		return Vector4D(target.GetX() / scale, target.GetY() / scale, target.GetZ() / scale, target.GetU() / scale);
	}
}