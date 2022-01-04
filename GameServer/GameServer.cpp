#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include "ThreadManager.h"

class TestLock
{
	USE_LOCK;

public:
	int32 TestRead()
	{
		READ_LOCK;

		if (_queue.empty())
			return -1;

		return _queue.front();
	}
	void TestPush(int32 value)
	{
		WRITE_LOCK;
		_queue.push(value);
	}
	void TestPop()
	{
		WRITE_LOCK;

		if (!_queue.empty())
			_queue.pop();
	}

private:
	queue<int32> _queue;
};

TestLock testLock;

void ThreadWrite()
{
	while (true)
	{
		testLock.TestPush(rand());
		this_thread::sleep_for(10ms);
		testLock.TestPop();
	}
}

void ThreadRead()
{
	while (true)
	{
		int32 read = testLock.TestRead();
		cout << read << endl;
		this_thread::sleep_for(1ms);
	}
}

int main()
{
	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadWrite);
	}

	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadRead);
	}

	GThreadManager->Join();

	return 0;
}
