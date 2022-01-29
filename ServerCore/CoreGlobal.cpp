#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"
#include "Memory.h"

ThreadManager* GThreadManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;
Memory* GMemory = nullptr;

CoreGlobal GCore;

CoreGlobal::CoreGlobal()
{
	GThreadManager = new ThreadManager();
	GDeadLockProfiler = new DeadLockProfiler();
	GMemory = new Memory();
}

CoreGlobal::~CoreGlobal()
{
	delete GThreadManager;
	delete GDeadLockProfiler;
	delete GMemory;
}
