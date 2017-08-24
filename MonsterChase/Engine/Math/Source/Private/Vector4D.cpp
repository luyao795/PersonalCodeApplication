#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <assert.h>
#include "Vector3D.h"
#include "Vector4D.h"

using namespace std;

namespace Engine
{
	Vector4D Vector4D::Normalize()
	{
		return Vector4D(xPos / GetLength(), yPos / GetLength(), zPos / GetLength(), uPos / GetLength());
	}

	float Vector4D::Dot(Vector4D & other)
	{
		return xPos * other.GetX() + yPos * other.GetY() + zPos * other.GetZ() + uPos * other.GetU();
	}

	float Vector4D::operator[](const size_t index)
	{
		assert(index >= 0 && index <= 3);
		if (index == 0)
			return xPos;
		else if (index == 1)
			return yPos;
		else if (index == 2)
			return zPos;
		else
			return uPos;
	}
}