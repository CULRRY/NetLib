#pragma once

/**
 * @class Lock
 * @brief RW SpinLock
 */

 /*--------------------------------------------
  [WWWWWWWW][WWWWWWWW][RRRRRRRR}[RRRRRRRR]
  W : WriteFlag (Exclusive Lock Owner ThreadID)
  R : ReadFlag (Shared Lock Count)
 ---------------------------------------------*/

class Lock
{
	static constexpr uint32
		ACQUIRE_TIMEOUT_TICK	= 10000,
		MAX_SPIN_COUNT			= 5000,
		WRITE_THREAD_MASK		= 0xFFFF'0000,
		READ_COUNT_MASK			= 0x0000'FFFF,
		EMPTY_FLAG				= 0x0000'0000;

public:
	void			WriteLock(const char* name);
	void			WriteUnlock(const char* name);
	void			ReadLock(const char* name);
	void			ReadUnlock(const char* name);

private:
	Atomic<uint32>	_lockFlag	= EMPTY_FLAG;
	uint16			_writeCount = 0;
};

