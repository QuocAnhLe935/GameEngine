#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>
//create a const expression that has a name 
constexpr float  MILLI_TO_SECS = 1000.f;

class Timer
{
public:
	//high resolution timer?
	//disable copy/move

	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&)=delete;
	Timer& operator=(Timer&&) = delete;

	Timer();
	~Timer();

	void Start();
	//Update every frames
	void UpdateFrameTicks();
	//what is the time between currentframe and previous frames
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;

	float GetCurrentTickMilli() const;
	float GetCurretTickSec() const;

private:
	//time is never negative amount of number availibe to 
	unsigned int prevTicks;
	unsigned int currentTicks;
};

#endif 