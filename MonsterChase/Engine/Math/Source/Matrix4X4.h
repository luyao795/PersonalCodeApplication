#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include "Vector4D.h"

namespace Engine
{
	class Matrix4X4
	{
	public:
		// Default constructor - Does Nothing. Initializing 16 floating point numbers
		// can be time consuming so we have a default constructor that does nothing.
		Matrix4X4() :
			m11(NAN)
		{
		}

		// Value based constructor - This is good for things like creating const matrix
		Matrix4X4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44) :
			m11(i_11), m12(i_12), m13(i_13), m14(i_14),
			m21(i_21), m22(i_22), m23(i_23), m24(i_24),
			m31(i_31), m32(i_32), m33(i_33), m34(i_34),
			m41(i_41), m42(i_42), m43(i_43), m44(i_44)
		{
		}

		Matrix4X4(Vector4D &xVec, Vector4D &yVec, Vector4D &zVec, Vector4D &uVec, bool areRowVec)
		{
			if (areRowVec)
			{
				m11 = xVec.GetX();
				m12 = xVec.GetY();
				m13 = xVec.GetZ();
				m14 = xVec.GetU();

				m21 = yVec.GetX();
				m22 = yVec.GetY();
				m23 = yVec.GetZ();
				m24 = yVec.GetU();

				m31 = zVec.GetX();
				m32 = zVec.GetY();
				m33 = zVec.GetZ();
				m34 = zVec.GetU();

				m41 = uVec.GetX();
				m42 = uVec.GetY();
				m43 = uVec.GetZ();
				m44 = uVec.GetU();
			}
			else
			{
				m11 = xVec.GetX();
				m21 = xVec.GetY();
				m31 = xVec.GetZ();
				m41 = xVec.GetU();

				m12 = yVec.GetX();
				m22 = yVec.GetY();
				m32 = yVec.GetZ();
				m42 = yVec.GetU();

				m13 = zVec.GetX();
				m23 = zVec.GetY();
				m33 = zVec.GetZ();
				m43 = zVec.GetU();

				m14 = uVec.GetX();
				m24 = uVec.GetY();
				m34 = uVec.GetZ();
				m44 = uVec.GetU();
			}
		}

		// Copy constructor for Matrix4X4. No need for move constructor as there is no pointer in this class.
		Matrix4X4(const Matrix4X4 &other) :
			m11(other.m11), m12(other.m12), m13(other.m13), m14(other.m14),
			m21(other.m21), m22(other.m22), m23(other.m23), m24(other.m24),
			m31(other.m31), m32(other.m32), m33(other.m33), m34(other.m34),
			m41(other.m41), m42(other.m42), m43(other.m43), m44(other.m44)
		{
		}

		// Inline getters and setters for individual elements.
		inline void Set11(const float value);
		inline void Set12(const float value);
		inline void Set13(const float value);
		inline void Set14(const float value);

		inline void Set21(const float value);
		inline void Set22(const float value);
		inline void Set23(const float value);
		inline void Set24(const float value);

		inline void Set31(const float value);
		inline void Set32(const float value);
		inline void Set33(const float value);
		inline void Set34(const float value);

		inline void Set41(const float value);
		inline void Set42(const float value);
		inline void Set43(const float value);
		inline void Set44(const float value);

		inline float Get11() const;
		inline float Get12() const;
		inline float Get13() const;
		inline float Get14() const;

		inline float Get21() const;
		inline float Get22() const;
		inline float Get23() const;
		inline float Get24() const;

		inline float Get31() const;
		inline float Get32() const;
		inline float Get33() const;
		inline float Get34() const;

		inline float Get41() const;
		inline float Get42() const;
		inline float Get43() const;
		inline float Get44() const;

		// Check whether the matrix is identity matrix.
		bool isIdentity();

		// Create Identity matrix.
		inline Matrix4X4 Identity() const;

		// Check whether the matrix is invertible by comparing its determinant to 0.
		inline bool isInvertible();

		// Determinant of this matrix.
		float Determinant();

		// Adjugate of this matrix.
		Matrix4X4 Adjugate();

		// Create Inverse matrix.
		Matrix4X4 Inverse();

		// Create Transpose matrix.
		Matrix4X4 Transpose();

		// Function to swap two elements. Used in Transpose().
		inline void Swap(float left, float right);

		// Vector is on the left side of this matrix.
		Vector4D MultiplyLeftVector(const Vector4D &left);
		// Vector is on the right side of this matrix.
		Vector4D MultiplyRightVector(const Vector4D &right);

		// Translation matrix for row vector.
		Matrix4X4 GetRowVectorTranslationMatrix(const Vector4D &translationRow);
		// Translation matrix for col vector.
		Matrix4X4 GetColVectorTranslationMatrix(const Vector4D &translationCol);
		// Rotation matrix for given radian.
		Matrix4X4 GetRotationMatrix(const float radian);

		// Assignment operator.
		void operator=(const Matrix4X4 &other);

		// Comparison operators.
		bool operator==(const Matrix4X4 &other);
		bool operator!=(const Matrix4X4 &other);

		// 4X4 Matrix addition.
		Matrix4X4 operator+=(const Matrix4X4 &other);
		// 4X4 Matrix subtraction.
		Matrix4X4 operator-=(const Matrix4X4 &other);
		// 4X4 Matrix Multiplication on left side of this matrix.
		Matrix4X4 MultiplyLeftMatrix(const Matrix4X4 &left);
		// 4X4 Matrix Multiplication on right side of this matrix.
		Matrix4X4 MultiplyRightMatrix(const Matrix4X4 &right);

		// Scaling operators.
		Matrix4X4 operator*=(const float scale);
		Matrix4X4 operator/=(const float scale);

		// Index operator.
		Vector4D operator[](const size_t index);

		// As for operator[], if desire to use matrix[m][n] to access the element at row m and column n,
		// overload operator[] for Matrix4X4 to return Vector4D and then overload operator[] for Vector4D to return float.

	private:
		float m11;
		float m12;
		float m13;
		float m14;
		float m21;
		float m22;
		float m23;
		float m24;
		float m31;
		float m32;
		float m33;
		float m34;
		float m41;
		float m42;
		float m43;
		float m44;
	};

	Matrix4X4 operator+(const Matrix4X4 &left, const Matrix4X4 &right);
	Matrix4X4 operator-(const Matrix4X4 &left, const Matrix4X4 &right);
	Matrix4X4 operator*(const Matrix4X4 &left, const Matrix4X4 &right);

	Matrix4X4 operator*(const Matrix4X4 &target, const float scale);
	Matrix4X4 operator/(const Matrix4X4 &target, const float scale);
}

#include "Matrix4X4.hpp"
#endif // !MATRIX4X4_H
