#include "pch.h"
#include "MemoryPool.h"

MemoryPool::MemoryPool(int32 allocSize)
	: _allocSize(allocSize)
{
}

MemoryPool::~MemoryPool()
{
	while (_queue.empty() == false)
	{
		MemoryHeader* header = _queue.front();
		_queue.pop();
		::free(header);
	}
}

void MemoryPool::Push(MemoryHeader* ptr)
{
	WRITE_LOCK;

	// 사용 안 하는 것으로 마킹
	ptr->allocSize = 0;

	// Pool에 메모리를 반납한다.
	_queue.push(ptr);
	_allocCount.fetch_sub(1);

}

MemoryHeader* MemoryPool::Pop()
{
	MemoryHeader* header = nullptr;

	{
		WRITE_LOCK;

		// Pool에 사용가능한 메모리가 있으면 꺼낸다.
		if (_queue.empty() == false)
		{
			header = _queue.front();
			_queue.pop();
		}
	}

	if (header == nullptr)
	{
		header = reinterpret_cast<MemoryHeader*>(::malloc(_allocSize));
	}
	else
	{
		// 사용하는 상태이면 크래시를 냅니다.
		ASSERT_CRASH(header->allocSize == 0);
	}

	_allocCount.fetch_add(1);

	return header;
}
