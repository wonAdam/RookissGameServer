#pragma once

extern class ThreadManager* GThreadManager;

extern class DeadLockProfiler* GDeadLockProfiler;

extern class Memory* GMemory;

class CoreGlobal
{
public:
	CoreGlobal();
	~CoreGlobal();
};

