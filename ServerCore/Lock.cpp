#include "pch.h"
#include "Lock.h"

void Lock::WriteLock()
{
	// 동일한 스레드가 소유하고 있다면 무조건 성공이다. writeCount만 1증가시킨다.
	const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 32;
	if (lockThreadId == LThreadId)
	{
		_writeCount++;
		return;
	}

	// 아무도 Write 및 Read하고 있지 않을 때, 경합해서 Write권을 얻는다.
	const int64 beginTick = ::GetTickCount64();
	const uint64 desired = ((((uint64)LThreadId) << 32) & WRITE_THREAD_MASK);
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; ++spinCount)
		{
			uint64 expected = EMPTY_FLAG;
			if (_lockFlag.compare_exchange_strong(OUT expected, desired))
			{
				_writeCount++;
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= AQUIRE_TIMEOUT_TICK)
			CRASH("LOCK_TIMEOUT");

		this_thread::yield();
	}

}

void Lock::WriteUnlock()
{
	// ReadLock을 다 풀기 전에는 WriteUnlock 불가능.
	if ((_lockFlag.load() & READ_COUNT_MASK) != 0)
		CRASH("INVALID_UNLOCK_ORDER");

	const int32 lockCount = --_writeCount;
	if (lockCount == 0)
		_lockFlag.store(EMPTY_FLAG);
}

void Lock::ReadLock()
{
	// 동일한 스레드가 소유하고 있다면 무조건 성공.

	const uint32 lockThreadId = (_lockFlag.load() & WRITE_THREAD_MASK) >> 32;
	if (lockThreadId == LThreadId)
	{
		_lockFlag.fetch_add(1);
		return;
	}

	// 아무도 Write하고 있지 않을 때 경합해서 공유카운트를 올린다.
	const int64 beginTick = ::GetTickCount64();
	while (true)
	{
		for (uint32 spinCount = 0; spinCount < MAX_SPIN_COUNT; ++spinCount)
		{
			uint64 expected = (_lockFlag.load() & READ_COUNT_MASK);
			if (_lockFlag.compare_exchange_strong(expected, expected + 1))
			{
				return;
			}
		}

		if (::GetTickCount64() - beginTick >= AQUIRE_TIMEOUT_TICK)
			CRASH("LOCK_TIMEOUT");

		this_thread::yield();
	}
}

void Lock::ReadUnlock()
{
	if ((_lockFlag.fetch_sub(1) & READ_COUNT_MASK) == 0) // 그 이전 값이 0...?!
		CRASH("MULTIPLE_UNLOCK");
}
