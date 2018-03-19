#pragma once

#include <functional>
#include <Windows.h>

namespace SoundToys
{
	enum class TimerType { start_now, delayed_start };
	class Timer
	{
	public:
		using Callback = std::function<void(bool)>;

		// If repeatDelayMS is 0, the timer will only fire after the initial delay.
		Timer(size_t initialDelayMS, size_t repeatDelayMS = 0, Callback cb = nullptr, TimerType type = TimerType::delayed_start);
		virtual ~Timer();

		void start();
		void stop();
	protected:
		void doCallback();
		void startIfAutoStarting(TimerType type);

	private:
		// if timerOrWaitFired == true, the timer expired (yes, this seems backwards).
		static void CALLBACK waitOrTimerCallback(void* lpParameter, BOOLEAN timerOrWaitFired);

		HANDLE m_timerHandle = nullptr;
		size_t m_initialDelayMS = 0;
		size_t m_repeatDelayMS = 0;
		bool m_calledOnce = false;
		Callback m_callback = nullptr;
	};
}