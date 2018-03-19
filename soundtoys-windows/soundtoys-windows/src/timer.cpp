#include "timer.hpp"
#include <iostream>

namespace SoundToys
{
	Timer::Timer(size_t initialDelayMS, size_t repeatDelayMS, Callback cb, TimerType type)
		: m_initialDelayMS(initialDelayMS)
		, m_repeatDelayMS(repeatDelayMS)
		, m_callback(cb)
	{	
		startIfAutoStarting(type);
	}

	Timer::~Timer()
	{
		stop();
	}

	void Timer::startIfAutoStarting(TimerType type)
	{
		if (type == TimerType::start_now)
		{
			start();
		}
	}

	void Timer::start()
	{
		stop();
		if (CreateTimerQueueTimer(&m_timerHandle, nullptr, waitOrTimerCallback, this, DWORD(m_initialDelayMS), DWORD(m_repeatDelayMS), WT_EXECUTEDEFAULT) != TRUE)
		{
			throw std::runtime_error("Failed to create timer");
		}
	}

	void Timer::stop()
	{
		if (m_timerHandle)
		{
			// CHECKME! Is the third argument here useful?
			DeleteTimerQueueTimer(nullptr, m_timerHandle, nullptr);
			m_timerHandle = nullptr;
		}
	}

	void Timer::doCallback()
	{
		if (m_callback) 
		{
			m_callback(m_calledOnce);
		}
		m_calledOnce = true;
	}

	void CALLBACK Timer::waitOrTimerCallback(void* lpParameter, BOOLEAN timerOrWaitFired)
	{
		Timer* timer = static_cast<Timer*>(lpParameter);
		if (timer && (timerOrWaitFired == TRUE))
		{
			timer->doCallback();
		}
		else
		{
			// CHECKME! Is this possible on a shutdown?
			std::cout << "Ignoring timer event" << std::endl;
		}
	}
}