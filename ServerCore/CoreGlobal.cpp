#include "pch.h"
#include "CoreGlobal.h"

#include "ThreadManager.h"
#include "DeadLockProfiler.h"

ThreadManager* GThreadManager = nullptr;
DeadLockProfiler* GDeadLockProfiler = nullptr;

CoreGlobal GCore;

CoreGlobal::CoreGlobal()
{
	GThreadManager = new ThreadManager();
	GDeadLockProfiler = new DeadLockProfiler();
}

CoreGlobal::~CoreGlobal()
{
	delete GThreadManager;
	delete GDeadLockProfiler;
}
