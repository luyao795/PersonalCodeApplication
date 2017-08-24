// Inline function definitions for Point2D class

#include <math.h>

namespace Engine
{
	inline float Point2D::GetX() const
	{
		return xPos;
	}

	inline float Point2D::GetY() const
	{
		return yPos;
	}

	inline void Point2D::SetX(const float x)
	{
		xPos = x;
	}

	inline void Point2D::SetY(const float y)
	{
		yPos = y;
	}

	inline void Point2D::MoveX(const float xDis)
	{
		xPos += xDis;
	}

	inline void Point2D::MoveY(const float yDis)
	{
		yPos += yDis;
	}

	inline bool Point2D::isZero()
	{
		return (xPos == 0.0f && yPos == 0.0f);
	}

	inline void Point2D::operator=(const Point2D &other)
	{
		xPos = other.GetX();
		yPos = other.GetY();
	}

	inline bool Point2D::operator==(const Point2D &other)
	{
		return (xPos == other.GetX() && yPos == other.GetY());
	}

	inline bool Point2D::operator!=(const Point2D &other)
	{
		return (xPos != other.GetX() || yPos != other.GetY());
	}

	inline Point2D Point2D::operator+=(const Point2D &other)
	{
		xPos += other.GetX();
		yPos += other.GetY();
		return *this;
	}

	inline Point2D Point2D::operator-=(const Point2D &other)
	{
		xPos -= other.GetX();
		yPos -= other.GetY();
		return *this;
	}

	inline Point2D Point2D::operator*=(const float scale)
	{
		xPos *= scale;
		yPos *= scale;
		return *this;
	}

	inline Point2D Point2D::operator/=(const float scale)
	{
		xPos /= scale;
		yPos /= scale;
		return *this;
	}

	inline Point2D operator+(const Point2D &left, const Point2D &right)
	{
		return Point2D(left.GetX() + right.GetX(), left.GetY() + right.GetY());
	}

	inline Point2D operator-(const Point2D &left, const Point2D &right)
	{
		return Point2D(left.GetX() - right.GetX(), left.GetY() - right.GetY());
	}

	inline Point2D operator*(const Point2D &target, const float scale)
	{
		return Point2D(target.GetX() * scale, target.GetY() * scale);
	}

	inline Point2D operator/(const Point2D &target, const float scale)
	{
		return Point2D(target.GetX() / scale, target.GetY() / scale);
	}

	// return true if target is NaN, return false otherwise
	/*inline bool CheckNaN(const float target)
	{
		volatile float value = target;
		return value != value;
	}

	inline bool AreAboutEqual(const float left, const float right)
	{
		const float epsilon = 0.0001f;
		return fabs(right - left) <= epsilon;
	}

	inline bool AreAboutEqual(const float left, const float right, const float epsilon)
	{
		return fabs(right - left) <= epsilon;
	}*/
}