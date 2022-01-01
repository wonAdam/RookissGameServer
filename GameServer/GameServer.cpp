#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <Windows.h>

#include "ConcurrentQueue.h"
#include "ConcurrentStack.h"

LockQueue<int32> q;
LockFreeStack<int32> s;

void StackPush()
{
	while (true)
	{
		int32 value = rand() % 100;
		s.Push(value);

		this_thread::sleep_for(10ms);
	}
}

//void StackWaitPop()
//{
//	while (true)
//	{
//		int32 data; 
//		s.WaitTillPop(OUT data);
//		cout << "StackWaitPop: " << data << endl;
//	}
//}

void StackTryPop()
{
	while (true)
	{
		int32 data;
		if (s.TryPop(OUT data))
		{
			cout << "StackTryPop: " << data << endl;
		}
	}
}
//
//void QueuePush()
//{
//	while (true)
//	{
//		int32 value = rand() % 100;
//		q.Push(value);
//
//		this_thread::sleep_for(10ms);
//	}
//}
//
//void QueueWaitPop()
//{
//	while (true)
//	{
//		int32 data;
//		q.WaitTillPop(OUT data);
//		cout << "QueueWaitPop: " << data << endl;
//	}
//}
//
//void QueueTryPop()
//{
//	while (true)
//	{
//		int32 data;
//		if (q.TryPop(OUT data))
//		{
//			cout << "QueueTryPop: " << data << endl;
//		}
//	}
//}


int main()
{
	srand((unsigned int)time(NULL));

	thread t1(StackPush);
	thread t2(StackTryPop);

	vector<thread> threads;
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(StackPush));
	}
	for (int i = 0; i < 5; i++)
	{
		threads.push_back(thread(StackTryPop));
	}
	//for (int i = 0; i < 5; i++)
	//{
	//	threads.push_back(thread(StackWaitPop));
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	threads.push_back(thread(QueuePush));
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	threads.push_back(thread(QueueTryPop));
	//}
	//for (int i = 0; i < 5; i++)
	//{
	//	threads.push_back(thread(QueueWaitPop));
	//}



	for (int i = 0 ; i < threads.size(); ++i)
		threads[i].join();

	return 0;
}
