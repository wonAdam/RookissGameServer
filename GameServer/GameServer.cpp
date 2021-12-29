#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include <thread>
#include <atomic>
#include <mutex>
#include <future>
#include <Windows.h>

atomic<bool> flag;

int main()
{
	flag = false;

	bool flagLockFree = flag.is_lock_free();
	cout << flagLockFree << endl;

	flag.store(true, memory_order::memory_order_seq_cst);

	bool val = flag.load(memory_order::memory_order_seq_cst);

	{
		/*bool prev = flag;
		flag = true;*/

		bool prev = flag.exchange(true);
	}

	// CAS Conpare and Swap 
	{
		bool expected = false;
		bool desired = true;
		flag.compare_exchange_strong(expected, desired);

		/*if (flag == expected)
		{
			flag = desired;
			return true;
		}
		else
		{
			expected = flag;
			return false;
		}*/
	}

	return 0;
}
