#include <Windows.h>
#include "Timer.h"

#define DESIRED_FPS				60.0f
#define DESIRED_FRAMETIME_MS	(1000.0f / DESIRED_FPS)
#define MAX_FRAMETIME_MS		(2 * DESIRED_FRAMETIME_MS)


using namespace std;

namespace Engine
{
	Timer * Timer::t = NULL;
	LARGE_INTEGER Timer::performanceCountStatic = {0};

	float Timer::CalculateFrameTimeInMS()
	{
		//Grab the GPU tick counter
		double currentTick = GetCounter();

		if (lastFrameStartTick)
		{
			// How many ticks have elapsed since we last did this
			double elapsedTicks = currentTick - lastFrameStartTick;

			// Calculate the frame time - converting ticks to ms.
			lastFrameTimeInMS = static_cast<float>(elapsedTicks / GetFrequency());
		}
		else
		{
			lastFrameTimeInMS = 16.67f;
		}
		// Note start of this frame
		lastFrameStartTick = static_cast<long long>(currentTick);

		return lastFrameTimeInMS;
	}

	float Timer::GetLastFrameTimeInMS()
	{
#ifdef CONSTANT_FRAMETIME
		return DESIRED_FRAMETIME_MS;
#elif defined CLAMP_FRAMETIME
		if (lastFrameTimeInMS > MAX_FRAMETIME_MS)
			return MAX_FRAMETIME_MS;
		else
			return lastFrameTimeInMS;
#else
		return lastFrameTimeInMS;
#endif //!CLAMP_FRAMETIME
	}

	double Timer::GetDiff(const double start, const double end)
	{
		return end - start;
	}

	double Timer::GetCounterStatic()
	{
		QueryPerformanceCounter(&performanceCountStatic);
		return static_cast<double>(performanceCountStatic.QuadPart);
	}

	Timer * Timer::Create()
	{
		if (!t)
			t = new Timer();
		return t;
	}

	double Timer::GetCounter()
	{
		QueryPerformanceCounter(&performanceCount);
		return static_cast<double>(performanceCount.QuadPart);
	}

	double Timer::GetFrequency()
	{
		if (frequency == 0.0f)
		{
			QueryPerformanceFrequency(&performanceFreq);
			frequency = static_cast<double>(performanceFreq.QuadPart) / 1000;
		}
		return frequency;
	}
}