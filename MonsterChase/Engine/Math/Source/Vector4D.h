#ifndef VECTOR4D_H
#define VECTOR4D_H

#include "Vector3D.h"

namespace Engine
{
	class Vector4D
	{
	public:
		Vector4D() :
			xPos(0.0f), yPos(0.0f), zPos(0.0f), uPos(0.0f)
		{
		}

		Vector4D(const float x, const float y, const float z, const float u) :
			xPos(x), yPos(y), zPos(z), uPos(u)
		{
		}

		Vector4D(const Vector3D vector, const float u) :
			xPos(vector.GetX()), yPos(vector.GetY()), zPos(vector.GetZ()), uPos(u)
		{
		}

		~Vector4D()
		{
		}

		inline float GetX() const;
		inline float GetY() const;
		inline float GetZ() const;
		inline float GetU() const;

		inline void SetX(const float x);
		inline void SetY(const float y);
		inline void SetZ(const float z);
		inline void SetU(const float u);

		inline void MoveX(const float xDis);
		inline void MoveY(const float yDis);
		inline void MoveZ(const float zDis);
		inline void MoveU(const float uDis);

		inline bool isZero();
		inline float GetLength() const;

		// Mathematical normalization.
		Vector4D Normalize();

		float Dot(Vector4D & other);

		inline void operator=(const Vector4D &other);
		inline bool operator==(const Vector4D &other);
		inline bool operator!=(const Vector4D &other);


		inline Vector4D operator+=(const Vector4D &other);
		inline Vector4D operator-=(const Vector4D &other);
		inline Vector4D operator*=(const float scale);
		inline Vector4D operator/=(const float scale);

		float operator[](const size_t index);

	private:
		float xPos;
		float yPos;
		float zPos;
		float uPos;
	};

	inline Vector4D operator+(const Vector4D &left, const Vector4D &right);
	inline Vector4D operator-(const Vector4D &left, const Vector4D &right);
	inline Vector4D operator*(const Vector4D &target, const float scale);
	inline Vector4D operator/(const Vector4D &target, const float scale);
}

#include "Vector4D.hpp"

#endif // !VECTOR4D_H
