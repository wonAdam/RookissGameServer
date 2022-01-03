#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include "ThreadManager.h"

void ThreadMain()
{
	while (true)
	{
		cout << "Hello !! I am thread... " << LThreadId << endl;
		this_thread::sleep_for(1s);
	}
}
int main()
{
	for (int32 i = 0; i < 5; ++i)
	{
		GThreadManager->Launch(ThreadMain);
	}

	GThreadManager->Join();

	return 0;
}
