#pragma once

/**
 * @class Lock
 * @brief RW SpinLock
 * @details
 * WriteLock 재귀적으로 사용가능.
 * W -> R 가능,
 * R -> W 불가능.
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


/**
 * @class ReadLockGuard
 * @brief lock은 실수를 방지하기 위해 무조건 LockGuard로만 사용.
 */
class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.ReadLock(name); }
	~ReadLockGuard() { _lock.ReadUnlock(_name); }

private:
	Lock&		_lock;
	const char* _name;
};

/**
 * @class WriteLockGuard
 * @brief lock은 실수를 방지하기 위해 무조건 LockGuard로만 사용.
 */
class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock, const char* name) : _lock(lock), _name(name) { _lock.WriteLock(name); }
	~WriteLockGuard() { _lock.WriteUnlock(_name); }

private:
	Lock&		_lock;
	const char* _name;
};