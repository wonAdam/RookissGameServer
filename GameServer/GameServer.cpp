#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "RefCounting.h"

#include "ThreadManager.h"
#include "Memory.h"
#include "Allocator.h"

class Knight
{
public:
	Knight()
	{
		std::cout << "Knight()" << std::endl;
	}

	~Knight()
	{
		std::cout << "~Knight()" << std::endl;
	}
		
	int32 _hp = 100;
	int32 _attack = 20;
};

int main()
{
	for (int i = 0; i < 5; ++i)
	{
		GThreadManager->Launch([]() 
			{
				while (true)
				{
					xVector<Knight> v(10);
					xMap<int32, Knight> m;
					m[100] = Knight();

					this_thread::sleep_for(10ms);
				}
			});
	}

	GThreadManager->Join();

	return 0;
}
