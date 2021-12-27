#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>

#include "UserManager.h"
#include "AccountManager.h"

void Func1()
{
	for (int32 i = 0; i < 100; ++i)
	{
		UserManager::Instance()->ProcessSave();
	}
}

void Func2()
{
	for (int32 i = 0; i < 100; ++i)
	{
		AccountManager::Instance()->ProcessLogin();
	}
}

int main()
{
	std::thread t1(Func1);
	std::thread t2(Func2);

	t1.join();
	t2.join();

	mutex m1;
	mutex m2;
	std::lock(m1, m2);

	lock_guard<mutex> g1(m1, std::adopt_lock);
	lock_guard<mutex> g2(m2, std::adopt_lock);

	return 0;
}
