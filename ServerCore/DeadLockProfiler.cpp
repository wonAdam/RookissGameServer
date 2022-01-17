#include "pch.h"
#include "DeadLockProfiler.h"
#include "CoreTLS.h"

void DeadLockProfiler::PushLock(const char* name)
{
	LockGuard _guard(_lock);

	int32 lockId = 0;

	auto findIt = _nameToId.find(name);
	if (findIt == _nameToId.end())
	{
		lockId = static_cast<int32>(_nameToId.size());
		_nameToId[name] = lockId;
		_idToName[lockId] = name;
	}
	else
	{
		lockId = findIt->second;
	}

	// 잡고 있는 락이 있고
	if (LLockStack.empty() == false)
	{
		const int32 prevId = LLockStack.top();
		if (lockId != prevId) // 이전 락을 다시 잠군게 아니고
		{
			// 기존에 발견되지 않은 케이스라면 데드락 여부를 다시 확인한다.
			set<int32>& history = _lockHistory[prevId];
			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}
	}

	LLockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(_lock);

	if (LLockStack.empty())
		CRASH("MULTIPLE_UNLOCK");

	int32 lockId = _nameToId[name];
	if (LLockStack.top() != lockId)
		CRASH("INVALID_UNLOCK");

	LLockStack.pop();
}

void DeadLockProfiler::CheckCycle()
{
	const int32 lockCount = static_cast<int32>(_nameToId.size());
	_discoveredOrder = vector<int32>(lockCount, -1);
	_discoveredCount = 0;
	_finished = vector<bool>(lockCount, false);
	_parent = vector<int32>(lockCount, -1);

	for (int32 lockId = 0; lockId < lockCount; ++lockId)
		DFS(lockId);

	// 연산 끝났으니 정리한다.
	_discoveredOrder.clear();
	_finished.clear();
	_parent.clear();
}

void DeadLockProfiler::DFS(int32 index)
{
	// 이미 방문을 했음
	if (_discoveredOrder[index] != -1)
		return;

	// 방문 순번을 기록
	_discoveredOrder[index] = _discoveredCount++;

	// 모든 인접한 정점을 순회한다.
	// _lockHistory : index락을 잡고 다른 락을 잡는 기록
	auto findIt = _lockHistory.find(index);
	if (findIt == _lockHistory.end()) // 인접한 노드가 없음
	{
		_finished[index] = true;
		return;
	}

	set<int32> nextSet = findIt->second;
	for (int32 next : nextSet)
	{
		// 아직 방문한 적이 없다면 방문하자
		if (_discoveredOrder[next] == -1)
		{
			_parent[next] = index;
			DFS(next);
			continue;
		}

		// index가 next보다 먼저 발견되었다면 next는 index의 후손이다. (순방향 간선)
		if (_discoveredOrder[index] < _discoveredOrder[next])
			continue;

		// 순방향이 아니고, 
		// DFS의 next번째 정점이 아직 종료되지 않았다면 next는 index의 선조이다. (역방향 간선)
		if (_finished[next] == false)
		{
			// logging & crash
			printf("%s -> %s\n ", _idToName[index], _idToName[next]);

			int32 now = index;
			while (true)
			{
				printf("%s -> %s\n ", _idToName[_parent[now]], _idToName[now]);
				now = _parent[now];
				if (now == next)
					break;
			}
			CRASH("DEADLOCK_DETECTED");
		}

	}

}
