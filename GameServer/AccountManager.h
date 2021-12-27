#pragma once
#include <mutex>

class Account
{

};

class AccountManager
{
public:
	static AccountManager* Instance()
	{
		static AccountManager instance;
		return &instance;
	}

	Account* GetAccount(int32 id)
	{
		lock_guard<mutex> guard(_mutex);

		// Get Account
		return nullptr;
	}

	void ProcessLogin();

private:
	mutex _mutex;
	map<int32, Account*> _accounts;
};

