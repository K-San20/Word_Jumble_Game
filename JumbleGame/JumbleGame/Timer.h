#ifndef _TIMER_H_
#define _TIMER_H_

#include <ctime>

class Timer
{
	unsigned int startTime;
public:
	Timer()
	{
		reset();
	}

	void reset()
	{
		startTime = clock();
	}

	unsigned int getElapsedTime()
	{
		return (clock() - startTime);
	}

	static void delay(const unsigned int milli)
	{
		unsigned int st = clock();
		while (clock() - st < milli){}
	}

};
#endif