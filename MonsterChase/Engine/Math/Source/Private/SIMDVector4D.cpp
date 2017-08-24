#include <xmmintrin.h>
#include <smmintrin.h>
#include "Vector4D.h"
#include "SIMDVector4D.h"

#define MM_SHUFFLE(fp3, fp2, fp1, fp0) ((fp3 << 6) | (fp2 << 4) | (fp1 << 2) | fp0)

using namespace std;

namespace Engine
{
	float Dot(const SIMDVector4D & left, const SIMDVector4D & right)
	{
		return _mm_cvtss_f32(_mm_dp_ps(left.GetVec(), right.GetVec(), 0x71));
	}

	SIMDVector4D Cross(const SIMDVector4D & left, const SIMDVector4D & right)
	{
		__m128 v1_swiz_op1 = _mm_shuffle_ps(left.GetVec(), left.GetVec(), MM_SHUFFLE(3, 0, 2, 1));
		__m128 v2_swiz_op1 = _mm_shuffle_ps(right.GetVec(), right.GetVec(), MM_SHUFFLE(3, 1, 0, 2));

		__m128 v1_swiz_op2 = _mm_shuffle_ps(left.GetVec(), left.GetVec(), _MM_SHUFFLE(3, 1, 0, 2));
		__m128 v2_swiz_op2 = _mm_shuffle_ps(right.GetVec(), right.GetVec(), _MM_SHUFFLE(3, 0, 2, 1));

		__m128 cross_op1 = _mm_mul_ps(v1_swiz_op1, v2_swiz_op1);
		__m128 cross_op2 = _mm_mul_ps(v1_swiz_op2, v2_swiz_op2);

		__m128 cross = _mm_sub_ps(cross_op1, cross_op2);

		return SIMDVector4D(cross);
	}

	SIMDVector4D operator+(const SIMDVector4D & left, const SIMDVector4D & right)
	{
		return SIMDVector4D(_mm_add_ps(left.GetVec(), right.GetVec()));
	}

	SIMDVector4D operator-(const SIMDVector4D & left, const SIMDVector4D & right)
	{
		return SIMDVector4D(_mm_sub_ps(left.GetVec(), right.GetVec()));
	}

	SIMDVector4D operator*(const SIMDVector4D & target, const float scale)
	{
		return SIMDVector4D(_mm_mul_ps(target.GetVec(), _mm_set_ps1(scale)));
	}

	SIMDVector4D operator/(const SIMDVector4D & target, const float scale)
	{
		return SIMDVector4D(_mm_div_ps(target.GetVec(), _mm_set_ps1(scale)));
	}
}
