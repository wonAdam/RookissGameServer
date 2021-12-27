#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

vector<int32> v;
mutex m;


void Push()
{
	for (int32 i = 0; i < 10'000; ++i)
	{
		std::lock_guard<std::mutex> lockGuard(m);
		v.push_back(i);
	}
}

int main()
{
	std::thread t1(Push);
	std::thread t2(Push);

	t1.join();
	t2.join();

	return 0;
}
