#include "Timer.h"

Timer::Timer() : prevTicks(0), currentTicks(0)
{
}

Timer::~Timer()
{
}

void Timer::Start()
{
	//sdl get ticks in millisec
	prevTicks = currentTicks = SDL_GetTicks();
}

void Timer::UpdateFrameTicks()
{
	//update with prev equal to current ticks then update current or when get delta time you get 0
	prevTicks = currentTicks;
	currentTicks = SDL_GetTicks();
}

float Timer::GetDeltaTime() const
{
	//get time from prev to current frame	
	return (currentTicks-prevTicks)/MILLI_TO_SECS;
}

//set and make sure your engine run 60 fps or get damaged to Graphic card :((
//make physics, networkings run consistent 
unsigned int Timer::GetSleepTime(const unsigned int fps_) const
{
	//calculate how many milliperfram depends of framerate we  want
	unsigned int milliSecsPerFrame = MILLI_TO_SECS / fps_;

	//no need to sleep amount of sleep is 0
	if (milliSecsPerFrame == 0){
		return 0;
	}

	//how much time does engine need to sleep
	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currentTicks);
	//don't want sleep too much 
	if (sleepTime > milliSecsPerFrame) {
		//return to wrk
		return milliSecsPerFrame;
	}
	//always sleep when needed
	return sleepTime;
}

float Timer::GetCurrentTickMilli() const
{
	return static_cast<float>(currentTicks);
}

float Timer::GetCurretTickSec() const
{
	
	return currentTicks/ MILLI_TO_SECS;
}
