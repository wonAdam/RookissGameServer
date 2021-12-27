#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

#include <future>

int64 Calculate()
{
	int64 sum = 0;
	for (int32 i = 0; i < 100'000; ++i)
	{
		sum += i;
	}

	return sum;
}

class Knight
{
public:
	int64 GetHp() { return 100; }
};

void PromiseWorker(std::promise<string>&& promise)
{
	promise.set_value("Secret Message");
}

void TaskWorker(std::packaged_task<int64(void)>&& task)
{
	task();
}

int main()
{
	// Synchronous
	int64 result = Calculate();

	// Future Asynchronous
	{
		std::future<int64> future = std::async(std::launch::async, Calculate);
	
		// do something ...
	
		future.wait();
		int64 result = future.get();
	}

	// Future Asynchronous - Object Method
	{
		Knight k;
	
		std::future<int64> future = std::async(std::launch::async, &Knight::GetHp, k);;
	
		int64 result = future.get();
	}

	// Promise
	{
		std::promise<string> promise;
		std::future<string> future = promise.get_future();
		
		thread t(PromiseWorker, std::move(promise));

		string msg = future.get();

		cout << msg << endl;

		t.join();
	}

	// Packaged Task
	{
		std::packaged_task<int64(void)> task(Calculate);
		std::future<int64> future = task.get_future();

		thread t(TaskWorker, std::move(task));

		int64 result = future.get();

		cout << result << endl;

		t.join();
	}

	return 0;
}
