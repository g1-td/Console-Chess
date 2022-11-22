#include "Timer.h"

Timer::Timer()
{
}

Timer::Timer(int _min, int _sec = 0, int _inc = 0)
{
	this->increment = std::chrono::seconds(_inc);
	this->time = std::chrono::minutes(_min) + std::chrono::seconds(_sec);
}

void Timer::start()
{
	run = true;
	
	while (!isZero() && run)
	{
		countDown();
	}
}

bool Timer::isZero() const
{
	return time == std::chrono::milliseconds(0);
}

void Timer::stop()
{
	run = false;
}

void Timer::addIncrement()
{
	time += std::chrono::duration_cast<std::chrono::milliseconds>(increment);
}

int Timer::getTimeMillis() const
{
	return time.count();
}

void Timer::countDown()
{
	auto t = std::chrono::milliseconds(100);
	
	std::this_thread::sleep_for(t);
	time -= std::chrono::milliseconds(t);
}
