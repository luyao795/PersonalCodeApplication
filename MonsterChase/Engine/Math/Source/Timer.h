#ifndef TIMER_H
#define TIMER_H

namespace Engine
{
	class Timer
	{
	public:
		static Timer * Create();
		double GetCounter();
		double GetFrequency();
		float CalculateFrameTimeInMS();
		float GetLastFrameTimeInMS();
		static double GetDiff(const double start, const double end);
		static double GetCounterStatic();

	private:
		float lastFrameTimeInMS;
		long long lastFrameStartTick = 0;
		LARGE_INTEGER performanceCount;
		LARGE_INTEGER performanceFreq;
		static LARGE_INTEGER performanceCountStatic;
		__int64 CounterStart = 0;
		double frequency = 0;
		static Timer * t;
	};

}

#endif // !TIMER_H
