#include <math.h>
#include "ValidityErrorChecker.h"

using namespace std;

namespace Engine
{
	bool CheckNaN(const float target)
	{
		volatile float value = target;
		return value != value;
	}

	bool AreAboutEqual(const float left, const float right)
	{
		const float epsilon = 0.00001f;
		return fabs(right - left) <= epsilon;
	}

	bool AreAboutEqual(const float left, const float right, const float epsilon)
	{
		return fabs(right - left) <= epsilon;
	}
}