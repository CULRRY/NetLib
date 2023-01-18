#include "pch.h"
#include "Lock.h"

void Lock::WriteLock(const char* name)
{
	const uint32 lockTreadID = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (lockTreadID == LThreadID)
	{
		_writeCount++;
		return;
	}

	const uint64 beginTick = ::GetTickCount64();
	const uint32 desired = (LThreadID << 16) & WRITE_THREAD_MASK;
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
			CRASH("Lock Timeout");

		this_thread::yield();
	}
}

void Lock::WriteUnlock(const char* name)
{
}

void Lock::ReadLock(const char* name)
{
}

void Lock::ReadUnlock(const char* name)
{
}
