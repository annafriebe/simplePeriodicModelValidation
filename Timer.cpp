#include "Timer.h"
#include <thread>

#define STEADY_CLOCK std::chrono::steady_clock
#define DURATION_CAST std::chrono::duration_cast
#define DURATION std::chrono::duration

Timer::Timer() :
	m_start(STEADY_CLOCK::now()),
	m_running(false),
	m_timePassed( 0 )
{}

void Timer::start()
{
	if (!m_running)
	{
		m_start = STEADY_CLOCK::now();
		m_running = true;
	}
}

void Timer::reset()
{
	m_start = STEADY_CLOCK::now();	
	m_running = true;
}

void Timer::stop()
{
	m_timePassed = timePassed();
	m_running = false;
}

double Timer::timePassed()
{
	if(m_running)
	{
		STEADY_CLOCK::time_point end;
		DURATION<double> time_span;

		// the time to count the difference is not included
		end = STEADY_CLOCK::now();
		time_span = DURATION_CAST<DURATION<double>>(end - m_start);
		return time_span.count();
	}
	else
	{
		return m_timePassed;
	}
}

double Timer::timeUntil(double unixTime)
{
	return unixTime - timePassed();
}

void Timer::sleepUntil(double seconds)
{
	DURATION<double> time_span(seconds);
	std::this_thread::sleep_until(m_start + time_span);
}

bool Timer::timeReached(double seconds)
{
	if (m_running && timePassed() > seconds)
	{
		return true;
	}
	return false;
}