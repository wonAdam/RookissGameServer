#include "pch.h"
#include "DeadLockProfiler.h"

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

	// 잡고 있는 락이 있었다면
	if (_lockStack.empty() == false)
	{
		// 기존에 발견되지 않은 케이스라면 데드락 여부 다시 확인한다.
		const int32 prevId = _lockStack.top();
		if (lockId != prevId)
		{
			set<int32>& history = _lockHistory[prevId];
			if (history.find(lockId) == history.end())
			{
				history.insert(lockId);
				CheckCycle();
			}
		}
	}

	_lockStack.push(lockId);
}

void DeadLockProfiler::PopLock(const char* name)
{
	LockGuard guard(_lock);

	if (_lockStack.empty())
		CRASH("MULTIPLE_UNLOCK");

	int32 lockId = _nameToId[name];
	if (_lockStack.top() != lockId)
		CRASH("INVALID_UNLOCK");

	_lockStack.pop();
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
	if (_discoveredOrder[index] != -1)
		return;

	_discoveredOrder[index] = _discoveredCount++;

	// 모든 인접한 정점을 순회한다.
	auto findIt = _lockHistory.find(index);
	if (findIt == _lockHistory.end())
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

		// 순방향이 아니고, DFS의 next번째 정점이 아직 종료되지 않았다면 next는 index의 선조이다. (역방향 간선)
		if (_finished[next] == false)
		{
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
