﻿#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "RefCounting.h"

#include "ThreadManager.h"
#include "Memory.h"

class Knight
{
public:
	Knight()
	{
		std::cout << "Kinght()" << std::endl;
	}

	~Knight()
	{
		std::cout << "~Kinght()" << std::endl;
	}

	// new operator overloading (Knight)
	static void* operator new(size_t size)
	{
		std::cout << "Knight new! " << size << std::endl;
		void* ptr = ::malloc(size);
		return ptr;
	}

	// delete operator overloading (Knight)
	static void operator delete(void* ptr)
	{
		std::cout << "Knight delete! " << std::endl;
		::free(ptr);
	}


private:
	int _hp = 100;
	int _attack = 15;
};

// new operator overloading (Global)
void* operator new(size_t size)
{
	std::cout << "new! " << size << std::endl;
	void* ptr = ::malloc(size);
	return ptr;
}

// delete operator overloading (Global)
void operator delete(void* ptr)
{
	std::cout << "delete! " << std::endl;
	::free(ptr);
}

// new operator overloading (Global)
void* operator new[](size_t size)
{
	std::cout << "new[]! " << size << std::endl;
	void* ptr = ::malloc(size);
	return ptr;
}

// delete operator overloading (Global)
void operator delete[](void* ptr)
{
	std::cout << "delete[]! " << std::endl;
	::free(ptr);
}


int main()
{
	//Knight* k = new Knight();
	Knight* k = xnew<Knight>();

	//delete k;
	xdelete(k);

	return 0;
}
