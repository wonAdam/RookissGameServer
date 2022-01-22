#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "RefCounting.h"

#include "ThreadManager.h"

class Wraith : public RefCountable
{
public:
	int _hp = 150;
	int _posX = 0;
	int _posY = 0;
};
using WraithRef = TSharedPtr<Wraith>;

class Missile : public RefCountable
{
public:
	void SetTarget(WraithRef target)
	{
		_target = target;
	}

	void Update()
	{
		if (_target == nullptr)
			return;

		int posX = _target->_posX;
		int posY = _target->_posY;

		// TODO: chasing

		if (_target->_hp == 0)
		{
			_target = nullptr;
		}
	}

private:
	WraithRef _target;
};
using MissileRef = TSharedPtr<Missile>;


int main()
{
	WraithRef wraith (new Wraith());
	Wraith* wCheck = &*wraith; // RefCount 확인용
	MissileRef missile (new Missile());
	Missile* mCheck = &*missile; // RefCount 확인용

	missile->SetTarget(wraith);

	// 레이스가 피격 당함
	wraith->_hp = 0;
	wraith = nullptr;

	// Game Loop
	while (true)
	{
		if (missile)
		{
			missile->Update();
		}
	}


	return 0;
}
