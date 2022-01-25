#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "RefCounting.h"

#include "ThreadManager.h"
#include "Memory.h"
#include "Allocator.h"

class Knight
{
	int32 _hp = 100;
	int32 _attack = 20;
};

int main()
{
	std::vector<Knight, STLAllocator<Knight>> v(100);

	return 0;
}
