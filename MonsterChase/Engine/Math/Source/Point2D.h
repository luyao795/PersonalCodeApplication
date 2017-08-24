#ifndef POINT2D_H
#define POINT2D_H

namespace Engine
{

	class Point2D
	{

	public:
		Point2D() :
			xPos(0.0f), yPos(0.0f)
		{
		}

		Point2D(const float x, const float y) :
			xPos(x), yPos(y)
		{
		}

		~Point2D()
		{
		}

		inline float GetX() const;
		inline float GetY() const;

		inline void SetX(const float x);
		inline void SetY(const float y);

		inline void MoveX(const float xDis);
		inline void MoveY(const float yDis);

		// Not mathematical normalization, just used for monster movement.
		Point2D Normalize();

		inline bool isZero();

		inline void operator=(const Point2D &other);
		inline bool operator==(const Point2D &other);
		inline bool operator!=(const Point2D &other);
		

		inline Point2D operator+=(const Point2D &other);
		inline Point2D operator-=(const Point2D &other);
		inline Point2D operator*=(const float scale);
		inline Point2D operator/=(const float scale);
		

	private:
		float xPos;
		float yPos;

	};

	inline Point2D operator+(const Point2D &left, const Point2D &right);
	inline Point2D operator-(const Point2D &left, const Point2D &right);
	inline Point2D operator*(const Point2D &target, const float scale);
	inline Point2D operator/(const Point2D &target, const float scale);
	//inline bool CheckNaN(const float target);
	//inline bool AreAboutEqual(const float left, const float right);
	//inline bool AreAboutEqual(const float left, const float right, const float epsilon);
	//int DebugPrint(const char* file, const char* func, const int line, const char* fmt, ...);

}
#include "Point2D.hpp"
#endif // POINT2D_H