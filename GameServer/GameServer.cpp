#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

//#include <Windows.h>

//int32 buffer[10000][10000];

int32 x = 0;
int32 y = 0;
int32 r1 = 0;
int32 r2 = 0;

volatile bool ready = false;

void Thread_1()
{
	while (!ready) { this_thread::yield(); }

	y = 1;
	r1 = x;
}

void Thread_2()
{
	while (!ready) { this_thread::yield(); }

	x = 1;
	r2 = y;
}


int main()
{
	int32 count = 0;

	while (true)
	{
		ready = false;
		count++;

		x = y = r1 = r2 = 0;

		thread t1(Thread_1);
		thread t2(Thread_2);

		ready = true;

		t1.join();
		t2.join();

		if (r1 == 0 && r2 == 0)
			break;
	}

	cout << count << "time for success" << endl;

	//memset(buffer, 0, sizeof(buffer));
	//
	//{
	//	uint64 start = GetTickCount64();
	//	int64 sum = 0;
	//	for (int32 i = 0; i < 10'000; ++i)
	//		for (int32 j = 0; j < 10'000; ++j)
	//			sum += buffer[i][j];
	//
	//	uint64 end = GetTickCount64();
	//	cout << "Elapsed Tick " << (end - start) << endl;
	//
	//}
	//
	//
	//{
	//	uint64 start = GetTickCount64();
	//	int64 sum = 0;
	//	for (int32 i = 0; i < 10'000; ++i)
	//		for (int32 j = 0; j < 10'000; ++j)
	//			sum += buffer[j][i];
	//
	//	uint64 end = GetTickCount64();
	//	cout << "Elapsed Tick " << (end - start) << endl;
	//
	//}



	return 0;
}
