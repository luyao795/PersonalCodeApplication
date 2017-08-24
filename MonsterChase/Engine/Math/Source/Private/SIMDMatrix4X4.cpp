#include "Matrix4X4.h"
#include "SIMDVector4D.h"
#include "SIMDMatrix4X4.h"

using namespace std;

namespace Engine
{
	SIMDVector4D Engine::SIMDMatrix4X4::MultiplyLeftVector(const Vector4D & left)
	{
		__m128 mulop1L = _mm_set_ps1(left.GetX());
		__m128 mulop1R = _mm_shuffle_ps(GetRow1(), GetRow1(), _MM_SHUFFLE(3, 2, 1, 0));

		__m128 mulop2L = _mm_set_ps1(left.GetY());
		__m128 mulop2R = _mm_shuffle_ps(GetRow2(), GetRow2(), _MM_SHUFFLE(3, 2, 1, 0));

		__m128 mulop3L = _mm_set_ps1(left.GetZ());
		__m128 mulop3R = _mm_shuffle_ps(GetRow3(), GetRow3(), _MM_SHUFFLE(3, 2, 1, 0));

		__m128 mulop4L = _mm_set_ps1(left.GetU());
		__m128 mulop4R = _mm_shuffle_ps(GetRow4(), GetRow4(), _MM_SHUFFLE(3, 2, 1, 0));

		__m128 mulop1 = _mm_mul_ps(mulop1L, mulop1R);
		__m128 mulop2 = _mm_mul_ps(mulop2L, mulop2R);
		__m128 mulop3 = _mm_mul_ps(mulop3L, mulop3R);
		__m128 mulop4 = _mm_mul_ps(mulop4L, mulop4R);

		__m128 addop1 = _mm_add_ps(mulop1, mulop2);
		__m128 addop2 = _mm_add_ps(mulop3, mulop4);
		__m128 addop3 = _mm_add_ps(addop1, addop2);

		return SIMDVector4D(addop3);
	}

	SIMDMatrix4X4 SIMDMatrix4X4::operator+=(const SIMDMatrix4X4 & other)
	{
		__m128 firstR = _mm_add_ps(row1, other.GetRow1());
		__m128 secndR = _mm_add_ps(row2, other.GetRow2());
		__m128 thirdR = _mm_add_ps(row3, other.GetRow3());
		__m128 forthR = _mm_add_ps(row4, other.GetRow4());

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 SIMDMatrix4X4::operator-=(const SIMDMatrix4X4 & other)
	{
		__m128 firstR = _mm_sub_ps(row1, other.GetRow1());
		__m128 secndR = _mm_sub_ps(row2, other.GetRow2());
		__m128 thirdR = _mm_sub_ps(row3, other.GetRow3());
		__m128 forthR = _mm_sub_ps(row4, other.GetRow4());

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 SIMDMatrix4X4::operator*=(const float scale)
	{
		__m128 scalVec = _mm_set_ps1(scale);

		__m128 firstR = _mm_mul_ps(row1, scalVec);
		__m128 secndR = _mm_mul_ps(row2, scalVec);
		__m128 thirdR = _mm_mul_ps(row3, scalVec);
		__m128 forthR = _mm_mul_ps(row4, scalVec);

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 SIMDMatrix4X4::operator/=(const float scale)
	{
		__m128 scalVec = _mm_set_ps1(scale);

		__m128 firstR = _mm_div_ps(row1, scalVec);
		__m128 secndR = _mm_div_ps(row2, scalVec);
		__m128 thirdR = _mm_div_ps(row3, scalVec);
		__m128 forthR = _mm_div_ps(row4, scalVec);

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 operator+(const SIMDMatrix4X4 & left, const SIMDMatrix4X4 & right)
	{
		__m128 firstR = _mm_add_ps(left.GetRow1(), right.GetRow1());
		__m128 secndR = _mm_add_ps(left.GetRow2(), right.GetRow2());
		__m128 thirdR = _mm_add_ps(left.GetRow3(), right.GetRow3());
		__m128 forthR = _mm_add_ps(left.GetRow4(), right.GetRow4());

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 operator-(const SIMDMatrix4X4 & left, const SIMDMatrix4X4 & right)
	{
		__m128 firstR = _mm_sub_ps(left.GetRow1(), right.GetRow1());
		__m128 secndR = _mm_sub_ps(left.GetRow2(), right.GetRow2());
		__m128 thirdR = _mm_sub_ps(left.GetRow3(), right.GetRow3());
		__m128 forthR = _mm_sub_ps(left.GetRow4(), right.GetRow4());

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 operator*(const SIMDMatrix4X4 & target, const float scale)
	{
		__m128 scalVec = _mm_set_ps1(scale);

		__m128 firstR = _mm_mul_ps(target.GetRow1(), scalVec);
		__m128 secndR = _mm_mul_ps(target.GetRow2(), scalVec);
		__m128 thirdR = _mm_mul_ps(target.GetRow3(), scalVec);
		__m128 forthR = _mm_mul_ps(target.GetRow4(), scalVec);

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}

	SIMDMatrix4X4 operator/(const SIMDMatrix4X4 & target, const float scale)
	{
		__m128 scalVec = _mm_set_ps1(scale);

		__m128 firstR = _mm_div_ps(target.GetRow1(), scalVec);
		__m128 secndR = _mm_div_ps(target.GetRow2(), scalVec);
		__m128 thirdR = _mm_div_ps(target.GetRow3(), scalVec);
		__m128 forthR = _mm_div_ps(target.GetRow4(), scalVec);

		return SIMDMatrix4X4(firstR, secndR, thirdR, forthR);
	}
}
