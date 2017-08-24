#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Point2D.h"

namespace Engine
{
	class Vector3D
	{
	public:
		Vector3D() :
			xPos(0.0f), yPos(0.0f), zPos(0.0f)
		{
		}

		Vector3D(const float x, const float y, const float z) :
			xPos(x), yPos(y), zPos(z)
		{
		}

		Vector3D(const Point2D point, const float z) :
			xPos(point.GetX()), yPos(point.GetY()), zPos(z)
		{
		}

		~Vector3D()
		{
		}

		inline float GetX() const;
		inline float GetY() const;
		inline float GetZ() const;

		inline void SetX(const float x);
		inline void SetY(const float y);
		inline void SetZ(const float z);

		inline void MoveX(const float xDis);
		inline void MoveY(const float yDis);
		inline void MoveZ(const float zDis);

		inline bool isZero();
		inline float GetLength() const;

		// Mathematical normalization.
		Vector3D Normalize();

		float Dot(Vector3D & other);

		inline void operator=(const Vector3D &other);
		inline bool operator==(const Vector3D &other);
		inline bool operator!=(const Vector3D &other);


		inline Vector3D operator+=(const Vector3D &other);
		inline Vector3D operator-=(const Vector3D &other);
		inline Vector3D operator*=(const float scale);
		inline Vector3D operator/=(const float scale);

	private:
		float xPos;
		float yPos;
		float zPos;
	};

	inline Vector3D operator+(const Vector3D &left, const Vector3D &right);
	inline Vector3D operator-(const Vector3D &left, const Vector3D &right);
	inline Vector3D operator*(const Vector3D &target, const float scale);
	inline Vector3D operator/(const Vector3D &target, const float scale);
}

#include "Vector3D.hpp"

#endif // !VECTOR3D_H
