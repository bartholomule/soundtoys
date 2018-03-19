#pragma once

#include <functional>

namespace SoundToys
{
	class ScopeExit
	{
	public:
		// Fairly useless default, nothing happens in destructor.
		ScopeExit() = default;
		ScopeExit(std::function<void()> atexit);
		ScopeExit(const ScopeExit&) = delete;
		ScopeExit(ScopeExit&& old);
		~ScopeExit();
		ScopeExit& operator=(ScopeExit&& old);
		ScopeExit& operator=(const ScopeExit&) = delete;

		// Cancel the atexit behavior of this object.
		void cancel();
	private:
		std::function<void()> m_atexit;
	};
}