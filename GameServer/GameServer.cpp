#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "RefCounting.h"

#include "ThreadManager.h"
#include "Memory.h"
#include "Allocator.h"
#include "ObjectPool.h"

class Knight
{
public:
	int32 _hp = rand() % 1000;
};

class Monster
{
public:
	int64 _id = 0;
};

int main()
{
	Knight* k = ObjectPool<Knight>::Pop();

	ObjectPool<Knight>::Push(k);

	// make_shared는 new delete를 사용한다.
	//shared_ptr<Knight> sptr = make_shared<Knight>();
	
	// 이렇게 shared_ptr이 내부적으로 객체를 만들때 사용할 함수를 지정해줄 수 있다.
	//shared_ptr<Knight> sptr = { ObjectPool<Knight>::Pop, ObjectPool<Knight>::Push };

	Knight* knights[100];

	for (int32 i = 0; i < 100; ++i)
		knights[i] = ObjectPool<Knight>::Pop();

	for (int32 i = 0; i < 100; ++i)
	{
		ObjectPool<Knight>::Push(knights[i]);
		knights[i] = nullptr;
	}

	shared_ptr<Knight> sptr = MakeShared<Knight>();

	for (int32 i = 0; i < 5; i++)
	{
		GThreadManager->Launch([]()
			{
				while (true)
				{
					Knight* knight = xnew<Knight>();

					cout << knight->_hp << endl;

					this_thread::sleep_for(10ms);

					xdelete(knight);
				}
			});
	}

	GThreadManager->Join();
}