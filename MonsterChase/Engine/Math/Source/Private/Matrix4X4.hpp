// Inline function definitions for Matrix4X4 class

#include <math.h>

namespace Engine
{
	inline Matrix4X4 Matrix4X4::Identity() const
	{
		return Matrix4X4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	inline bool Matrix4X4::isInvertible()
	{
		if (Determinant() == 0.0f)
			return false;
		else
			return true;
	}

	inline void Matrix4X4::Swap(float left, float right)
	{
		float temp = left;
		left = right;
		right = temp;
	}

	inline void Matrix4X4::Set11(const float value)
	{
		m11 = value;
	}

	inline void Matrix4X4::Set12(const float value)
	{
		m12 = value;
	}

	inline void Matrix4X4::Set13(const float value)
	{
		m13 = value;
	}

	inline void Matrix4X4::Set14(const float value)
	{
		m14 = value;
	}

	inline void Matrix4X4::Set21(const float value)
	{
		m21 = value;
	}

	inline void Matrix4X4::Set22(const float value)
	{
		m22 = value;
	}

	inline void Matrix4X4::Set23(const float value)
	{
		m23 = value;
	}

	inline void Matrix4X4::Set24(const float value)
	{
		m24 = value;
	}

	inline void Matrix4X4::Set31(const float value)
	{
		m31 = value;
	}

	inline void Matrix4X4::Set32(const float value)
	{
		m32 = value;
	}

	inline void Matrix4X4::Set33(const float value)
	{
		m33 = value;
	}

	inline void Matrix4X4::Set34(const float value)
	{
		m34 = value;
	}

	inline void Matrix4X4::Set41(const float value)
	{
		m41 = value;
	}

	inline void Matrix4X4::Set42(const float value)
	{
		m42 = value;
	}

	inline void Matrix4X4::Set43(const float value)
	{
		m43 = value;
	}

	inline void Matrix4X4::Set44(const float value)
	{
		m44 = value;
	}

	inline float Matrix4X4::Get11() const
	{
		return m11;
	}

	inline float Matrix4X4::Get12() const
	{
		return m12;
	}

	inline float Matrix4X4::Get13() const
	{
		return m13;
	}

	inline float Matrix4X4::Get14() const
	{
		return m14;
	}

	inline float Matrix4X4::Get21() const
	{
		return m21;
	}

	inline float Matrix4X4::Get22() const
	{
		return m22;
	}

	inline float Matrix4X4::Get23() const
	{
		return m23;
	}

	inline float Matrix4X4::Get24() const
	{
		return m24;
	}

	inline float Matrix4X4::Get31() const
	{
		return m31;
	}

	inline float Matrix4X4::Get32() const
	{
		return m32;
	}

	inline float Matrix4X4::Get33() const
	{
		return m33;
	}

	inline float Matrix4X4::Get34() const
	{
		return m34;
	}

	inline float Matrix4X4::Get41() const
	{
		return m41;
	}

	inline float Matrix4X4::Get42() const
	{
		return m42;
	}

	inline float Matrix4X4::Get43() const
	{
		return m43;
	}

	inline float Matrix4X4::Get44() const
	{
		return m44;
	}
}