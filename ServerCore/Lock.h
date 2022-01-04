#pragma once

#include "Types.h"

// Lock 정책 (중복해서 재귀적으로 Lock을 허용하는 경우)
// W -> W (O)
// R -> R (O)
// W -> R (O)
// R -> W (X)
class Lock
{
	enum : uint64
	{
		AQUIRE_TIMEOUT_TICK = 10000,
		MAX_SPIN_COUNT = 5000,
		WRITE_THREAD_MASK = 0xFFFF'FFFF'0000'0000,
		READ_COUNT_MASK = 0x0000'0000'FFFF'FFFF,
		EMPTY_FLAG = 0x0000'0000'0000'0000
	};

public:
	void WriteLock();
	void WriteUnlock();
	void ReadLock();
	void ReadUnlock();

private:
	Atomic<uint64> _lockFlag = EMPTY_FLAG;
	uint32 _writeCount = 0;
};

class ReadLockGuard
{
public:
	ReadLockGuard(Lock& lock) : _lock(lock) { _lock.ReadLock(); }
	~ReadLockGuard() { _lock.ReadUnlock(); }

private:
	Lock& _lock;
};

class WriteLockGuard
{
public:
	WriteLockGuard(Lock& lock) : _lock(lock) { _lock.WriteLock(); }
	~WriteLockGuard() { _lock.WriteUnlock(); }

private:
	Lock& _lock;
};