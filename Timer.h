#pragma once
#include <chrono>
#include <thread>


class Timer
{
	public:
	Timer();
	Timer(int minutes, int seconds, int increment);

	void start();
	void stop();
	void addIncrement();
	void countDown();
	int getTimeMillis() const;
	bool isZero() const;

	private:
	std::chrono::milliseconds time = std::chrono::milliseconds(0);
	std::chrono::seconds increment = std::chrono::seconds(0);
	bool run = false;
};

