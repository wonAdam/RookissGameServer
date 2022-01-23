#pragma once

#define CRASH(cause)						\
{											\
	uint32* crash = nullptr;				\
	__analysis_assume(crash != nullptr);	\
	*crash = 911;							\
}											

#define ASSERT_CRASH(expr)					\
{											\
	if (!(expr))							\
	{										\
		CRASH("ASSERT_CRASH");				\
		__analysis_assume(expr);			\
	}										\
}					

#define OUT 
#define IN 

#define USE_MANY_LOCKS(count)	Lock _locks[count];
#define USE_LOCK				USE_MANY_LOCKS(1)
#define READ_LOCK_IDX(idx)		ReadLockGuard readLockGuard_##idx(_locks[idx], typeid(this).name());
#define READ_LOCK				READ_LOCK_IDX(0)
#define WRITE_LOCK_IDX(idx)		WriteLockGuard writeLockGuard_##idx(_locks[idx], typeid(this).name());
#define WRITE_LOCK				WRITE_LOCK_IDX(0)

#ifdef _DEBUG
#define xALLOC(size) StompAllocator::Alloc(size)
#define xRELEASE(ptr) StompAllocator::Release(ptr)
#else
#define xALLOC(size) BaseAllocator::Alloc(size)
#define xRELEASE(ptr) BaseAllocator::Release(ptr)
#endif