#include "pch.h"
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
		std::cout << "Knight()" << std::endl;
	}

	Knight(int hp, int attack) : _hp(hp), _attack(attack) 
	{
		std::cout << "Knight(" << hp << ", " << attack << ")" << std::endl;
	}

	~Knight()
	{
		std::cout << "~Knight()" << std::endl;
	}

	//// new operator overloading (Knight)
	//static void* operator new(size_t size)
	//{
	//	std::cout << "Knight new! " << size << std::endl;
	//	void* ptr = ::malloc(size);
	//	return ptr;
	//}

	//// delete operator overloading (Knight)
	//static void operator delete(void* ptr)
	//{
	//	std::cout << "Knight delete! " << std::endl;
	//	::free(ptr);
	//}


public:
	int _hp = 100;
	int _attack = 15;
};

//// new operator overloading (Global)
//void* operator new(size_t size)
//{
//	std::cout << "new! " << size << std::endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//// delete operator overloading (Global)
//void operator delete(void* ptr)
//{
//	std::cout << "delete! " << std::endl;
//	::free(ptr);
//}
//
//// new operator overloading (Global)
//void* operator new[](size_t size)
//{
//	std::cout << "new[]! " << size << std::endl;
//	void* ptr = ::malloc(size);
//	return ptr;
//}
//
//// delete operator overloading (Global)
//void operator delete[](void* ptr)
//{
//	std::cout << "delete[]! " << std::endl;
//	::free(ptr);
//}


int main()
{
	Knight* k1 = xnew<Knight>();
	Knight* k2 = xnew<Knight>(500, 80);

	xdelete(k1);
	xdelete(k2);

	k2->_hp = 10;

	//int* num = new int;
	//*num = 100;

	//int64 address = reinterpret_cast<int64>(num);
	//std::cout << address << std::endl;

	//delete num;

	//SYSTEM_INFO info;
	//::GetSystemInfo(&info);

	//Knight* k1 = new Knight();

	//int* test = (int*)::VirtualAlloc(NULL, 4, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	//*test = 100;
	//::VirtualFree(test, 0, MEM_RELEASE);

	//*test = 20;

	return 0;
}
