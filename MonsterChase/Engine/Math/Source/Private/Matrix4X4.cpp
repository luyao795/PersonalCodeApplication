#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include "DebugPrint.h"
#include "Vector4D.h"
#include "ValidityErrorChecker.h"
#include "Matrix4X4.h"

using namespace std;

namespace Engine
{
	bool Matrix4X4::isIdentity()
	{
		if (m11 != 1.0f || m22 != 1.0f || m33 != 1.0f || m44 != 1.0f)
			return false;
		else
		{
			if (m12 == 0.0f && m13 == 0.0f && m14 == 0.0f &&
				m21 == 0.0f && m23 == 0.0f && m24 == 0.0f &&
				m31 == 0.0f && m32 == 0.0f && m34 == 0.0f &&
				m41 == 0.0f && m42 == 0.0f && m43 == 0.0f)
				return true;
			else
				return false;
		}
	}

	float Matrix4X4::Determinant()
	{
		assert(!CheckNaN(m11));
		float det;
		det = m14 * m23 * m32 * m41 - m13 * m24 * m32 * m41 - m14 * m22 * m33 * m41 + m12 * m24 * m33 * m41 +
			  m13 * m22 * m34 * m41 - m12 * m23 * m34 * m41 - m14 * m23 * m31 * m42 + m13 * m24 * m31 * m42 +
			  m14 * m21 * m33 * m42 - m11 * m24 * m33 * m42 - m13 * m21 * m34 * m42 + m11 * m23 * m34 * m42 +
			  m14 * m22 * m31 * m43 - m12 * m24 * m31 * m43 - m14 * m21 * m32 * m43 + m11 * m24 * m32 * m43 +
			  m12 * m21 * m34 * m43 - m11 * m22 * m34 * m43 - m13 * m22 * m31 * m44 + m12 * m23 * m31 * m44 +
			  m13 * m21 * m32 * m44 - m11 * m23 * m32 * m44 - m12 * m21 * m33 * m44 + m11 * m22 * m33 * m44;
		return det;
	}

	Matrix4X4 Matrix4X4::Adjugate()
	{
		assert(!CheckNaN(m11));
		float b11 = m22 * m33 * m44 + m23 * m34 * m42 + m24 * m32 * m43 - m22 * m34 * m43 - m23 * m32 * m44 - m24 * m33 * m42;
		float b12 = m12 * m34 * m43 + m13 * m32 * m44 + m14 * m33 * m42 - m12 * m33 * m44 - m13 * m34 * m42 - m14 * m32 * m43;
		float b13 = m12 * m23 * m44 + m13 * m24 * m42 + m14 * m22 * m43 - m12 * m24 * m43 - m13 * m22 * m44 - m14 * m23 * m42;
		float b14 = m12 * m24 * m33 + m13 * m22 * m34 + m14 * m23 * m32 - m12 * m23 * m34 - m13 * m24 * m32 - m14 * m22 * m33;
		float b21 = m21 * m34 * m43 + m23 * m31 * m44 + m24 * m33 * m41 - m21 * m33 * m44 - m23 * m34 * m41 - m24 * m31 * m43;
		float b22 = m11 * m33 * m44 + m13 * m34 * m41 + m14 * m31 * m43 - m11 * m34 * m43 - m13 * m31 * m44 - m14 * m33 * m41;
		float b23 = m11 * m24 * m43 + m13 * m21 * m44 + m14 * m23 * m41 - m11 * m23 * m44 - m13 * m24 * m41 - m14 * m21 * m43;
		float b24 = m11 * m23 * m34 + m13 * m24 * m31 + m14 * m21 * m33 - m11 * m24 * m33 - m13 * m21 * m34 - m14 * m23 * m31;
		float b31 = m21 * m32 * m44 + m22 * m34 * m41 + m24 * m31 * m42 - m21 * m34 * m42 - m22 * m31 * m44 - m24 * m32 * m41;
		float b32 = m11 * m34 * m42 + m12 * m31 * m44 + m14 * m32 * m41 - m11 * m32 * m44 - m12 * m34 * m41 - m14 * m31 * m42;
		float b33 = m11 * m22 * m44 + m12 * m24 * m41 + m14 * m21 * m42 - m11 * m24 * m42 - m12 * m21 * m44 - m14 * m22 * m41;
		float b34 = m11 * m24 * m32 + m12 * m21 * m34 + m14 * m22 * m31 - m11 * m22 * m34 - m12 * m24 * m31 - m14 * m21 * m32;
		float b41 = m21 * m33 * m42 + m22 * m31 * m43 + m23 * m32 * m41 - m21 * m32 * m43 - m22 * m33 * m41 - m23 * m31 * m42;
		float b42 = m11 * m32 * m43 + m12 * m33 * m41 + m13 * m31 * m42 - m11 * m33 * m42 - m12 * m31 * m43 - m13 * m32 * m41;
		float b43 = m11 * m23 * m42 + m12 * m21 * m43 + m13 * m22 * m41 - m11 * m22 * m43 - m12 * m23 * m41 - m13 * m21 * m42;
		float b44 = m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32 - m11 * m23 * m32 - m12 * m21 * m33 - m13 * m22 * m31;

		Matrix4X4 adj(b11, b12, b13, b14,
					  b21, b22, b23, b24,
					  b31, b32, b33, b34,
					  b41, b42, b43, b44);
		return adj;
	}

	Matrix4X4 Matrix4X4::Transpose()
	{
		assert(!CheckNaN(m11));
		Matrix4X4 result(*this);
		result.Swap(m12, m21);
		result.Swap(m13, m31);
		result.Swap(m14, m41);
		result.Swap(m23, m32);
		result.Swap(m24, m42);
		result.Swap(m34, m43);
		return result;
	}

	Matrix4X4 Matrix4X4::Inverse()
	{
		if (!isInvertible())
		{
			Matrix4X4 result = Matrix4X4();
			result.Set11(NAN);
			DebugPrint(__FILE__, __FUNCTION__, __LINE__, "Warning: Matrix not invertible, empty matrix returned.\n");
			return result;
		}
		else
		{
			Matrix4X4 mat = Adjugate();
			float det = Determinant();
			mat /= det;
			return mat;
		}
	}

	// Row Vector Translation Matrix:
	// [1, 0, 0, 0]
	// [0, 1, 0, 0]
	// [0, 0, 1, 0]
	// [x, y, z, 1]
	Matrix4X4 Matrix4X4::GetRowVectorTranslationMatrix(const Vector4D &translationRow)
	{
		Matrix4X4 rowTrans = Identity();
		rowTrans.Set41(translationRow.GetX());
		rowTrans.Set42(translationRow.GetY());
		rowTrans.Set43(translationRow.GetZ());

		return rowTrans;
	}

	// Col Vector Translation Matrix:
	// [1, 0, 0, x]
	// [0, 1, 0, y]
	// [0, 0, 1, z]
	// [0, 0, 0, 1]
	Matrix4X4 Matrix4X4::GetColVectorTranslationMatrix(const Vector4D &translationCol)
	{
		Matrix4X4 colTrans = Identity();
		colTrans.Set14(translationCol.GetX());
		colTrans.Set24(translationCol.GetY());
		colTrans.Set34(translationCol.GetZ());

		return colTrans;
	}

	// Rotation Matrix for angle i in radian:
	// [+cos i, -sin i, 0, 0]
	// [+sin i, +cos i, 0, 0]
	// [     0,      0, 1, 0]
	// [     0,      0, 0, 1]
	Matrix4X4 Matrix4X4::GetRotationMatrix(const float radian)
	{
		Matrix4X4 rot = Identity();
		float cosRot = cosf(radian);
		float sinRot = sinf(radian);
		rot.Set11(cosRot);
		rot.Set12(-1.0f * sinRot);
		rot.Set21(sinRot);
		rot.Set22(cosRot);

		return rot;
	}

	Vector4D Matrix4X4::MultiplyLeftVector(const Vector4D &left)
	{
		float x = left.GetX() * m11 + left.GetY() * m21 + left.GetZ() * m31 + left.GetU() * m41;
		float y = left.GetX() * m12 + left.GetY() * m22 + left.GetZ() * m32 + left.GetU() * m42;
		float z = left.GetX() * m13 + left.GetY() * m23 + left.GetZ() * m33 + left.GetU() * m43;
		float u = left.GetX() * m14 + left.GetY() * m24 + left.GetZ() * m34 + left.GetU() * m44;

		return Vector4D(x, y, z, u);
	}

	Vector4D Matrix4X4::MultiplyRightVector(const Vector4D &right)
	{
		float x = m11 * right.GetX() + m12 * right.GetY() + m13 * right.GetZ() + m14 * right.GetU();
		float y = m21 * right.GetX() + m22 * right.GetY() + m23 * right.GetZ() + m24 * right.GetU();
		float z = m31 * right.GetX() + m32 * right.GetY() + m33 * right.GetZ() + m34 * right.GetU();
		float u = m41 * right.GetX() + m42 * right.GetY() + m43 * right.GetZ() + m44 * right.GetU();

		return Vector4D(x, y, z, u);
	}

	void Matrix4X4::operator=(const Matrix4X4 &other)
	{
		m11 = other.Get11();
		m12 = other.Get12();
		m13 = other.Get13();
		m14 = other.Get14();

		m21 = other.Get21();
		m22 = other.Get22();
		m23 = other.Get23();
		m24 = other.Get24();

		m31 = other.Get31();
		m32 = other.Get32();
		m33 = other.Get33();
		m34 = other.Get34();

		m41 = other.Get41();
		m42 = other.Get42();
		m43 = other.Get43();
		m44 = other.Get44();
	}

	bool Matrix4X4::operator==(const Matrix4X4 &other)
	{
		bool isSame = (m11 == other.Get11() && m12 == other.Get12() && m13 == other.Get13() && m14 == other.Get14() &&
					   m21 == other.Get21() && m22 == other.Get22() && m23 == other.Get23() && m24 == other.Get24() &&
					   m31 == other.Get31() && m32 == other.Get32() && m33 == other.Get33() && m34 == other.Get34() &&
					   m41 == other.Get41() && m42 == other.Get42() && m43 == other.Get43() && m44 == other.Get44());
		return isSame;
	}

	bool Matrix4X4::operator!=(const Matrix4X4 &other)
	{
		bool isSame = (m11 == other.Get11() && m12 == other.Get12() && m13 == other.Get13() && m14 == other.Get14() &&
			m21 == other.Get21() && m22 == other.Get22() && m23 == other.Get23() && m24 == other.Get24() &&
			m31 == other.Get31() && m32 == other.Get32() && m33 == other.Get33() && m34 == other.Get34() &&
			m41 == other.Get41() && m42 == other.Get42() && m43 == other.Get43() && m44 == other.Get44());
		return !isSame;
	}

	Vector4D Matrix4X4::operator[](const size_t index)
	{
		assert(index >= 0 && index <= 3);
		if (index == 0)
			return Vector4D(m11, m12, m13, m14);
		else if (index == 1)
			return Vector4D(m21, m22, m23, m24);
		else if (index == 2)
			return Vector4D(m31, m32, m33, m34);
		else
			return Vector4D(m41, m42, m42, m44);
	}

	Matrix4X4 Matrix4X4::operator*=(const float scale)
	{
		m11 *= scale;
		m12 *= scale;
		m13 *= scale;
		m14 *= scale;

		m21 *= scale;
		m22 *= scale;
		m23 *= scale;
		m24 *= scale;

		m31 *= scale;
		m32 *= scale;
		m33 *= scale;
		m34 *= scale;

		m41 *= scale;
		m42 *= scale;
		m43 *= scale;
		m44 *= scale;

		return *this;
	}

	Matrix4X4 Matrix4X4::operator/=(const float scale)
	{
		m11 /= scale;
		m12 /= scale;
		m13 /= scale;
		m14 /= scale;

		m21 /= scale;
		m22 /= scale;
		m23 /= scale;
		m24 /= scale;

		m31 /= scale;
		m32 /= scale;
		m33 /= scale;
		m34 /= scale;

		m41 /= scale;
		m42 /= scale;
		m43 /= scale;
		m44 /= scale;

		return *this;
	}

	Matrix4X4 Matrix4X4::operator+=(const Matrix4X4 &other)
	{
		m11 += other.Get11();
		m12 += other.Get12();
		m13 += other.Get13();
		m14 += other.Get14();

		m21 += other.Get21();
		m22 += other.Get22();
		m23 += other.Get23();
		m24 += other.Get24();

		m31 += other.Get31();
		m32 += other.Get32();
		m33 += other.Get33();
		m34 += other.Get34();

		m41 += other.Get41();
		m42 += other.Get42();
		m43 += other.Get43();
		m44 += other.Get44();

		return *this;
	}

	Matrix4X4 Matrix4X4::operator-=(const Matrix4X4 &other)
	{
		m11 -= other.Get11();
		m12 -= other.Get12();
		m13 -= other.Get13();
		m14 -= other.Get14();
		
		m21 -= other.Get21();
		m22 -= other.Get22();
		m23 -= other.Get23();
		m24 -= other.Get24();

		m31 -= other.Get31();
		m32 -= other.Get32();
		m33 -= other.Get33();
		m34 -= other.Get34();

		m41 -= other.Get41();
		m42 -= other.Get42();
		m43 -= other.Get43();
		m44 -= other.Get44();

		return *this;
	}

	Matrix4X4 Matrix4X4::MultiplyLeftMatrix(const Matrix4X4 &left)
	{
		float r11 = left.Get11() * m11 + left.Get12() * m21 + left.Get13() * m31 + left.Get14() * m41;
		float r12 = left.Get11() * m12 + left.Get12() * m22 + left.Get13() * m32 + left.Get14() * m42;
		float r13 = left.Get11() * m13 + left.Get12() * m23 + left.Get13() * m33 + left.Get14() * m43;
		float r14 = left.Get11() * m14 + left.Get12() * m24 + left.Get13() * m34 + left.Get14() * m44;

		float r21 = left.Get21() * m11 + left.Get22() * m21 + left.Get23() * m31 + left.Get24() * m41;
		float r22 = left.Get21() * m12 + left.Get22() * m22 + left.Get23() * m32 + left.Get24() * m42;
		float r23 = left.Get21() * m13 + left.Get22() * m23 + left.Get23() * m33 + left.Get24() * m43;
		float r24 = left.Get21() * m14 + left.Get22() * m24 + left.Get23() * m34 + left.Get24() * m44;

		float r31 = left.Get31() * m11 + left.Get32() * m21 + left.Get33() * m31 + left.Get34() * m41;
		float r32 = left.Get31() * m12 + left.Get32() * m22 + left.Get33() * m32 + left.Get34() * m42;
		float r33 = left.Get31() * m13 + left.Get32() * m23 + left.Get33() * m33 + left.Get34() * m43;
		float r34 = left.Get31() * m14 + left.Get32() * m24 + left.Get33() * m34 + left.Get34() * m44;

		float r41 = left.Get41() * m11 + left.Get42() * m21 + left.Get43() * m31 + left.Get44() * m41;
		float r42 = left.Get41() * m12 + left.Get42() * m22 + left.Get43() * m32 + left.Get44() * m42;
		float r43 = left.Get41() * m13 + left.Get42() * m23 + left.Get43() * m33 + left.Get44() * m43;
		float r44 = left.Get41() * m14 + left.Get42() * m24 + left.Get43() * m34 + left.Get44() * m44;

		Matrix4X4 leftMul(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return leftMul;
	}

	Matrix4X4 Matrix4X4::MultiplyRightMatrix(const Matrix4X4 &right)
	{
		float r11 = m11 * right.Get11() + m12 * right.Get21() + m13 * right.Get31() + m14 * right.Get41();
		float r12 = m11 * right.Get12() + m12 * right.Get22() + m13 * right.Get32() + m14 * right.Get42();
		float r13 = m11 * right.Get13() + m12 * right.Get23() + m13 * right.Get33() + m14 * right.Get43();
		float r14 = m11 * right.Get14() + m12 * right.Get24() + m13 * right.Get34() + m14 * right.Get44();

		float r21 = m21 * right.Get11() + m22 * right.Get21() + m23 * right.Get31() + m24 * right.Get41();
		float r22 = m21 * right.Get12() + m22 * right.Get22() + m23 * right.Get32() + m24 * right.Get42();
		float r23 = m21 * right.Get13() + m22 * right.Get23() + m23 * right.Get33() + m24 * right.Get43();
		float r24 = m21 * right.Get14() + m22 * right.Get24() + m23 * right.Get34() + m24 * right.Get44();

		float r31 = m31 * right.Get11() + m32 * right.Get21() + m33 * right.Get31() + m34 * right.Get41();
		float r32 = m31 * right.Get12() + m32 * right.Get22() + m33 * right.Get32() + m34 * right.Get42();
		float r33 = m31 * right.Get12() + m32 * right.Get22() + m33 * right.Get32() + m34 * right.Get42();
		float r34 = m31 * right.Get14() + m32 * right.Get24() + m33 * right.Get34() + m34 * right.Get44();

		float r41 = m41 * right.Get11() + m42 * right.Get21() + m43 * right.Get31() + m44 * right.Get41();
		float r42 = m41 * right.Get12() + m42 * right.Get22() + m43 * right.Get32() + m44 * right.Get42();
		float r43 = m41 * right.Get12() + m42 * right.Get22() + m43 * right.Get32() + m44 * right.Get42();
		float r44 = m41 * right.Get14() + m42 * right.Get24() + m43 * right.Get34() + m44 * right.Get44();

		Matrix4X4 rightMul(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return rightMul;
	}

	Matrix4X4 operator+(const Matrix4X4 &left, const Matrix4X4 &right)
	{
		float r11 = left.Get11() + right.Get11();
		float r12 = left.Get12() + right.Get12();
		float r13 = left.Get13() + right.Get13();
		float r14 = left.Get14() + right.Get14();

		float r21 = left.Get21() + right.Get21();
		float r22 = left.Get22() + right.Get22();
		float r23 = left.Get23() + right.Get23();
		float r24 = left.Get24() + right.Get24();

		float r31 = left.Get31() + right.Get31();
		float r32 = left.Get32() + right.Get32();
		float r33 = left.Get33() + right.Get33();
		float r34 = left.Get34() + right.Get34();

		float r41 = left.Get41() + right.Get41();
		float r42 = left.Get42() + right.Get42();
		float r43 = left.Get43() + right.Get43();
		float r44 = left.Get44() + right.Get44();

		Matrix4X4 addRes(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return addRes;
	}

	Matrix4X4 operator-(const Matrix4X4 &left, const Matrix4X4 &right)
	{
		float r11 = left.Get11() - right.Get11();
		float r12 = left.Get12() - right.Get12();
		float r13 = left.Get13() - right.Get13();
		float r14 = left.Get14() - right.Get14();

		float r21 = left.Get21() - right.Get21();
		float r22 = left.Get22() - right.Get22();
		float r23 = left.Get23() - right.Get23();
		float r24 = left.Get24() - right.Get24();

		float r31 = left.Get31() - right.Get31();
		float r32 = left.Get32() - right.Get32();
		float r33 = left.Get33() - right.Get33();
		float r34 = left.Get34() - right.Get34();

		float r41 = left.Get41() - right.Get41();
		float r42 = left.Get42() - right.Get42();
		float r43 = left.Get43() - right.Get43();
		float r44 = left.Get44() - right.Get44();

		Matrix4X4 subRes(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return subRes;
	}

	Matrix4X4 operator*(const Matrix4X4 &left, const Matrix4X4 &right)
	{
		float r11 = left.Get11() * right.Get11() + left.Get12() * right.Get21() + left.Get13() * right.Get31() + left.Get14() * right.Get41();
		float r12 = left.Get11() * right.Get12() + left.Get12() * right.Get22() + left.Get13() * right.Get32() + left.Get14() * right.Get42();
		float r13 = left.Get11() * right.Get13() + left.Get12() * right.Get23() + left.Get13() * right.Get33() + left.Get14() * right.Get43();
		float r14 = left.Get11() * right.Get14() + left.Get12() * right.Get24() + left.Get13() * right.Get34() + left.Get14() * right.Get44();

		float r21 = left.Get21() * right.Get11() + left.Get22() * right.Get21() + left.Get23() * right.Get31() + left.Get24() * right.Get41();
		float r22 = left.Get21() * right.Get12() + left.Get22() * right.Get22() + left.Get23() * right.Get32() + left.Get24() * right.Get42();
		float r23 = left.Get21() * right.Get13() + left.Get22() * right.Get23() + left.Get23() * right.Get33() + left.Get24() * right.Get43();
		float r24 = left.Get21() * right.Get14() + left.Get22() * right.Get24() + left.Get23() * right.Get34() + left.Get24() * right.Get44();

		float r31 = left.Get31() * right.Get11() + left.Get32() * right.Get21() + left.Get33() * right.Get31() + left.Get34() * right.Get41();
		float r32 = left.Get31() * right.Get12() + left.Get32() * right.Get22() + left.Get33() * right.Get32() + left.Get34() * right.Get42();
		float r33 = left.Get31() * right.Get13() + left.Get32() * right.Get23() + left.Get33() * right.Get33() + left.Get34() * right.Get43();
		float r34 = left.Get31() * right.Get14() + left.Get32() * right.Get24() + left.Get33() * right.Get34() + left.Get34() * right.Get44();

		float r41 = left.Get41() * right.Get11() + left.Get42() * right.Get21() + left.Get43() * right.Get31() + left.Get44() * right.Get41();
		float r42 = left.Get41() * right.Get12() + left.Get42() * right.Get22() + left.Get43() * right.Get32() + left.Get44() * right.Get42();
		float r43 = left.Get41() * right.Get13() + left.Get42() * right.Get23() + left.Get43() * right.Get33() + left.Get44() * right.Get43();
		float r44 = left.Get41() * right.Get14() + left.Get42() * right.Get24() + left.Get43() * right.Get34() + left.Get44() * right.Get44();

		Matrix4X4 mul(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return mul;
	}

	Matrix4X4 operator*(const Matrix4X4 &target, const float scale)
	{
		float r11 = target.Get11() * scale;
		float r12 = target.Get12() * scale;
		float r13 = target.Get13() * scale;
		float r14 = target.Get14() * scale;

		float r21 = target.Get21() * scale;
		float r22 = target.Get22() * scale;
		float r23 = target.Get23() * scale;
		float r24 = target.Get24() * scale;

		float r31 = target.Get31() * scale;
		float r32 = target.Get32() * scale;
		float r33 = target.Get33() * scale;
		float r34 = target.Get34() * scale;

		float r41 = target.Get41() * scale;
		float r42 = target.Get42() * scale;
		float r43 = target.Get43() * scale;
		float r44 = target.Get44() * scale;

		Matrix4X4 scaleMat(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return scaleMat;
	}

	Matrix4X4 operator/(const Matrix4X4 &target, const float scale)
	{
		float r11 = target.Get11() / scale;
		float r12 = target.Get12() / scale;
		float r13 = target.Get13() / scale;
		float r14 = target.Get14() / scale;

		float r21 = target.Get21() / scale;
		float r22 = target.Get22() / scale;
		float r23 = target.Get23() / scale;
		float r24 = target.Get24() / scale;

		float r31 = target.Get31() / scale;
		float r32 = target.Get32() / scale;
		float r33 = target.Get33() / scale;
		float r34 = target.Get34() / scale;

		float r41 = target.Get41() / scale;
		float r42 = target.Get42() / scale;
		float r43 = target.Get43() / scale;
		float r44 = target.Get44() / scale;

		Matrix4X4 scaleMat(r11, r12, r13, r14, r21, r22, r23, r24, r31, r32, r33, r34, r41, r42, r43, r44);
		return scaleMat;
	}
}