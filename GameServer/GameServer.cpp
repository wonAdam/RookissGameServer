#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <Windows.h>

mutex m;
queue<int32> q;
HANDLE h;

void Producer()
{
	while (true)
	{
		{
			unique_lock<mutex> lock(m);
			q.push(100);
		}

		::SetEvent(h);

		this_thread::sleep_for(100ms);
	}
}

void Consumer()
{
	while (true)
	{
		::WaitForSingleObject(h, INFINITE);

		vector<int32> v;
		bool isPopped = false;
		{
			unique_lock<mutex> lock(m);
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
	h = ::CreateEvent(NULL, FALSE, FALSE, NULL);

	std::thread t1(Producer);
	std::thread t2(Consumer);

	t1.join();
	t2.join();

	::CloseHandle(h);

	return 0;
}
