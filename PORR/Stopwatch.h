#pragma once

#include <chrono>

typedef std::chrono::microseconds TimeT;
typedef std::chrono::high_resolution_clock ClockT;
typedef double DurationT;

class Stopwatch
{
private:
	std::chrono::time_point<ClockT> _start, _end;
public:
	Stopwatch() { start(); }
	void start() { _start = _end = ClockT::now(); }
	DurationT stop() { _end = ClockT::now(); return elapsed(); }
	DurationT elapsed() {
		std::chrono::time_point<ClockT> _end = ClockT::now();
		auto delta = std::chrono::duration_cast<TimeT>(_end - _start);
		return delta.count();
	}
};