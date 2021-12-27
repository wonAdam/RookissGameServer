#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

mutex m;
queue<int32> q;

condition_variable cv;

void Producer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}
		cv.notify_one();

		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	while (true)
	{
		unique_lock<mutex> lock(m);
		cv.wait(lock, []() -> bool { return !q.empty(); });

		vector<int32> v;
		bool isPopped = false;
		{
			while (q.empty() == false)
			{
				v.push_back(q.front());
				q.pop();
				isPopped = true;
			}
		}

		if (isPopped)
		{
			for(const int& e : v)
				cout << e << endl;
		}
	}
}

int main()
{
	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	return 0;
}
