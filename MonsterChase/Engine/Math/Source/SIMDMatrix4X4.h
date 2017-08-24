#ifndef SIMDMATRIX4X4_H
#define SIMDMATRIX4X4_H

namespace Engine
{
	class SIMDMatrix4X4
	{
	public:
		SIMDMatrix4X4() :
			row1(_mm_setzero_ps()),
			row2(_mm_setzero_ps()),
			row3(_mm_setzero_ps()),
			row4(_mm_setzero_ps())
		{
		}

		SIMDMatrix4X4(const Matrix4X4 & mat) :
			row1(_mm_set_ps(mat.Get14(), mat.Get13(), mat.Get12(), mat.Get11())),
			row2(_mm_set_ps(mat.Get24(), mat.Get23(), mat.Get22(), mat.Get21())),
			row3(_mm_set_ps(mat.Get34(), mat.Get33(), mat.Get32(), mat.Get31())),
			row4(_mm_set_ps(mat.Get44(), mat.Get43(), mat.Get42(), mat.Get41()))
		{
		}


		SIMDMatrix4X4(const __m128 r1, const __m128 r2, const __m128 r3, const __m128 r4) :
			row1(r1), row2(r2), row3(r3), row4(r4)
		{
		}

		SIMDMatrix4X4(const SIMDMatrix4X4 & other) :
			row1(other.row1), row2(other.row2), row3(other.row3), row4(other.row4)
		{
		}

		__m128 GetRow1() const
		{
			return row1;
		}

		__m128 GetRow2() const
		{
			return row2;
		}

		__m128 GetRow3() const
		{
			return row3;
		}

		__m128 GetRow4() const
		{
			return row4;
		}

		SIMDVector4D GetRowVector1() const
		{
			return SIMDVector4D(row1);
		}

		SIMDVector4D GetRowVector2() const
		{
			return SIMDVector4D(row2);
		}

		SIMDVector4D GetRowVector3() const
		{
			return SIMDVector4D(row3);
		}

		SIMDVector4D GetRowVector4() const
		{
			return SIMDVector4D(row4);
		}

		void SetRow1(const __m128 r1)
		{
			row1 = r1;
		}

		void SetRow2(const __m128 r2)
		{
			row2 = r2;
		}

		void SetRow3(const __m128 r3)
		{
			row3 = r3;
		}

		void SetRow4(const __m128 r4)
		{
			row4 = r4;
		}

		void SetRowVector1(const SIMDVector4D & rv1)
		{
			row1 = rv1.GetVec();
		}

		void SetRowVector2(const SIMDVector4D & rv2)
		{
			row2 = rv2.GetVec();
		}

		void SetRowVector3(const SIMDVector4D & rv3)
		{
			row3 = rv3.GetVec();
		}

		void SetRowVector4(const SIMDVector4D & rv4)
		{
			row4 = rv4.GetVec();
		}

		SIMDVector4D MultiplyLeftVector(const Vector4D & left);

		SIMDMatrix4X4 Identity()
		{
			SIMDMatrix4X4 mat;
			mat.SetRow1(_mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
			mat.SetRow2(_mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f));
			mat.SetRow3(_mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f));
			mat.SetRow4(_mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f));
			return mat;
		}

		SIMDMatrix4X4 operator+=(const SIMDMatrix4X4 & other);
		SIMDMatrix4X4 operator-=(const SIMDMatrix4X4 & other);
		SIMDMatrix4X4 operator*=(const float scale);
		SIMDMatrix4X4 operator/=(const float scale);

	private:
		__m128 row1;
		__m128 row2;
		__m128 row3;
		__m128 row4;
	};

	SIMDMatrix4X4 operator+(const SIMDMatrix4X4 & left, const SIMDMatrix4X4 & right);
	SIMDMatrix4X4 operator-(const SIMDMatrix4X4 & left, const SIMDMatrix4X4 & right);

	SIMDMatrix4X4 operator*(const SIMDMatrix4X4 & target, const float scale);
	SIMDMatrix4X4 operator/(const SIMDMatrix4X4 & target, const float scale);
}

#endif // !SIMDMATRIX4X4_H
