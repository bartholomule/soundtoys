#include "simplelock.hpp"

namespace SoundToys
{
	bool SimpleLock::tryLock()
	{
		return InterlockedExchange(&m_value, TRUE) == FALSE;
	}

	void SimpleLock::unlock()
	{
		InterlockedExchange(&m_value, FALSE);
	}

	SimpleLock::LockScope::LockScope(SimpleLock& lock)
		: m_lock(lock)
		, m_lockAcquired(m_lock.tryLock())
	{
	}

	SimpleLock::LockScope::LockScope(LockScope&& scope)
		: m_lock(scope.m_lock)
		, m_lockAcquired(scope.m_lockAcquired)
	{
		scope.m_lockAcquired = false;
	}

	SimpleLock::LockScope::~LockScope()
	{
		if (m_lockAcquired) {
			m_lock.unlock();
		}
	}

	SimpleLock::LockScope SimpleLock::grabLock()
	{
		return LockScope(*this);
	}
}