#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include "Point2D.h"
#include "Vector3D.h"

using namespace std;

namespace Engine
{
	Vector3D Vector3D::Normalize()
	{
		return Vector3D(xPos / GetLength(), yPos / GetLength(), zPos / GetLength());
	}

	float Vector3D::Dot(Vector3D & other)
	{
		return xPos * other.GetX() + yPos * other.GetY() + zPos * other.GetZ();
	}
}