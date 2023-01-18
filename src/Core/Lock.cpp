#include "pch.h"
#include "Lock.h"

void Lock::WriteLock(const char* name)
{
	const uint32 lockTreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (lockTreadId == LThreadID)
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
		{
			CRASH("Lock Timeout");
		}

		this_thread::yield();
	}
}

void Lock::WriteUnlock(const char* name)
{
	if ((_lockFlag.load() & READ_COUNT_MASK) != 0)
	{
		CRASH("Invalid unlock mask");
	}

	const int32 lockCount = --_writeCount;
	if (lockCount == 0)
	{
		_lockFlag.store(EMPTY_FLAG);
	}
}

void Lock::ReadLock(const char* name)
{
	const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 16;
	if (lockThreadId == LThreadID)
	{
		_lockFlag.fetch_add(1);
		return;
	}

	const uint64 beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; spinCount++)
		{
			uint32 expected = _lockFlag & READ_COUNT_MASK;
			if (_lockFlag.compare_exchange_strong(expected, expected + 1));
			{
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= ACQUIRE_TIMEOUT_TICK)
		{
			CRASH("Lock Timeout");
		}

		this_thread::yield();
	}
}

void Lock::ReadUnlock(const char* name)
{
	if ((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0)
	{
		CRASH("Multiple Unlock");
	}
}
