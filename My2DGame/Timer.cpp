#include "Timer.h"

Timer::Timer()
{
	Reset();
}

void Timer::Reset()
{
	_startTime = std::chrono::steady_clock::now();
	_lastFrameTime = std::chrono::steady_clock::now();
}

double Timer::Elapsed() const
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = now - _startTime;
	return duration.count();
}

void Timer::Update()
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<double> duration = now - _lastFrameTime;
	_deltaTime = duration.count();
	_lastFrameTime = now;
}

bool Timer::Release()
{
	return true;
}