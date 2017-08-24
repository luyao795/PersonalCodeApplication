#ifndef SIMDVECTOR4D_H
#define SIMDVECTOR4D_H

#include <xmmintrin.h>
#include <smmintrin.h>

namespace Engine
{
	class SIMDVector4D
	{
	public:
		SIMDVector4D() :
			vec(_mm_setzero_ps())
		{
		}

		SIMDVector4D(const float x, const float y, const float z, const float u) :
			vec(_mm_set_ps(u, z, y, x))
		{
		}

		SIMDVector4D(const Vector4D vector) :
			vec(_mm_set_ps(vector.GetU(), vector.GetZ(), vector.GetY(), vector.GetX()))
		{
		}

		SIMDVector4D(const SIMDVector4D & copy) :
			vec(copy.vec)
		{
		}

		SIMDVector4D(const __m128 vect) :
			vec(vect)
		{
		}

		__m128 GetVec() const
		{
			return vec;
		}

		__m128 SetVec(const __m128 vector)
		{
			vec = vector;

			return vec;
		}

		float GetLength() const
		{
			return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(vec, vec, 0x71)));
		}

		// Intrinsic version of normalization, only for first 3 components.
		SIMDVector4D Normalize()
		{
			// Version 1, faster but less accurate.
			__m128 inverse = _mm_rsqrt_ps(_mm_dp_ps(vec, vec, 0x77));
			return _mm_mul_ps(vec, inverse);

			// Version 2, slower but more accurate.
			//__m128 inv = _mm_sqrt_ps(_mm_dp_ps(vec, vec, 0x7F));
			//return _mm_div_ps(vec, inv);
		}

		void operator=(const SIMDVector4D & other)
		{
			vec = other.GetVec();
		}

		SIMDVector4D operator+=(const SIMDVector4D & other)
		{
			return SIMDVector4D(_mm_add_ps(vec, other.GetVec()));
		}

		SIMDVector4D operator-=(const SIMDVector4D & other)
		{
			return SIMDVector4D(_mm_sub_ps(vec, other.GetVec()));
		}

		SIMDVector4D operator*=(const float scale)
		{
			return SIMDVector4D(_mm_mul_ps(vec, _mm_set_ps1(scale)));
		}

		SIMDVector4D operator/=(const float scale)
		{
			return SIMDVector4D(_mm_div_ps(vec, _mm_set_ps1(scale)));
		}

	private:
		__m128 vec;
	};

	SIMDVector4D operator+(const SIMDVector4D & left, const SIMDVector4D & right);
	SIMDVector4D operator-(const SIMDVector4D & left, const SIMDVector4D & right);
	SIMDVector4D operator*(const SIMDVector4D & target, const float scale);
	SIMDVector4D operator/(const SIMDVector4D & target, const float scale);

	float Dot(const SIMDVector4D & left, const SIMDVector4D & right);
	SIMDVector4D Cross(const SIMDVector4D & left, const SIMDVector4D & right);
}

#endif // !SIMDVECTOR4D_H
