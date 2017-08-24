#ifndef ACCUMULATOR_H
#define ACCUMULATOR_H

#include <limits>
#include <stdint.h>

namespace Engine
{
	class Accumulator
	{
	public:
		Accumulator(const char * name) :
			sum(0.0),
			count(0),
			minV((std::numeric_limits<float>::max)()),
			maxV((std::numeric_limits<float>::min)())
		{
		}

		void operator+=(float time)
		{
			sum += time;
			count++;

			if (time > maxV)
				maxV = time;
			else if (time < minV)
				minV = time;
		}

		float Average()
		{
			return static_cast<float>(sum / count);
		}

	private:
		double sum;
		uint64_t count;
		float minV, maxV;
	};
}

#endif // !ACCUMULATOR_H
