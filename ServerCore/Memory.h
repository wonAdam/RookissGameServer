#pragma once
#include "Allocator.h"

class MemoryPool;

class Memory
{
	enum
	{
		// ~1024까지 32단위 => 32개의 32바이트짜리 메모리풀들
		// ~2048까지 128단위 => 8개의 128바이트짜리 메모리풀들
		// ~4096까지 256단위 => 8개의 256바이트짜리 메모리풀들
		POOL_COUNT = (1024 / 32) + (1048 / 128) + (2048 / 256),
		MAX_ALLOC_SIZE = 4096
	};

public:
	Memory();
	~Memory();

	void* Allocate(int32 size);
	void Release(void* ptr);

private:
	vector<MemoryPool*> _pools;

	// 메모리의 크기 <-> 메모리 풀
	MemoryPool* _poolTable[MAX_ALLOC_SIZE + 1];
	
};

template<typename Type, typename... Args>
Type* xnew(Args&&... args)
{
	// memory allocation
	Type* memory = static_cast<Type*>(xALLOC(sizeof(Type)));

	// constructor
	new(memory)Type(std::forward<Args>(args)...);

	return memory;
}

template<typename Type>
void xdelete(Type* obj)
{
	xRELEASE(obj);
}