#include "scopeexit.hpp"

namespace SoundToys
{
	ScopeExit::ScopeExit(std::function<void()> atexit)
		: m_atexit(std::move(atexit))
	{
	}

	ScopeExit::ScopeExit(ScopeExit&& old)
		: m_atexit()
	{
		std::swap(m_atexit, old.m_atexit);
	}

	ScopeExit::~ScopeExit() {
		if (m_atexit) {
			m_atexit();
		}
	}

	ScopeExit& ScopeExit::operator=(ScopeExit&& old)
	{
		std::swap(m_atexit, old.m_atexit);
		return *this;
	}

	void ScopeExit::cancel()
	{
		m_atexit = nullptr;
	}
}