#pragma once

#include <stack>
#include <map>
#include <vector>

class DeadLockProfiler
{
public:
	void PushLock(const char* name);
	void PopLock(const char* name);
	void CheckCycle();

private:
	void DFS(int32 index);

private:
	unordered_map<const char*, int32>	_nameToId;
	unordered_map<int32, const char*>	_idToName;
	map<int32, set<int32>>				_lockHistory; // key번 lock이 value번 lock을 잡은 적이 있다.

	Mutex _lock;

private:
	vector<int32> _discoveredOrder;		// 정점이 발견된 순서를 기록하는 배열
	int32 _discoveredCount = 0;			// 노드가 발견된 순서
	vector<bool> _finished;				// dfs i번째가 종료되었는지
	vector<int32> _parent;
};

