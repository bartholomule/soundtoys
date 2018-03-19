#pragma once

#include <Windows.h>

namespace SoundToys
{
	class SimpleLock
	{
	public:
		bool tryLock();
		void unlock();

		class LockScope
		{
		public:
			LockScope(SimpleLock& lock);
			LockScope(LockScope&& scope);
			~LockScope();
		private:
			SimpleLock& m_lock;
			bool m_lockAcquired;
		};

		LockScope grabLock();

	private:
		long m_value = FALSE;
	};
}