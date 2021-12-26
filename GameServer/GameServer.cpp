#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>

void HelloThread()
{
	std::cout << "Hello Thread !!" << std::endl;
}

#include <string>

void HelloThread2(std::string print)
{
	std::cout << print << std::endl;
}

void HelloThread3(int num)
{
	std::cout << num << std::endl;
}

int main()
{
	vector<std::thread> v;
	for (int32 i = 0; i < 10; ++i)
	{
		v.push_back(std::thread(HelloThread3, i));
	}

	for (int32 i = 0; i < 10; ++i)
	{
		if (v[i].joinable())
			v[i].join();
	}

	cout << "Hello Main" << endl;

	return 0;
}
