#pragma once
class AccountManager
{
	USE_LOCK;

public:
	void Account_ThenPlayer();
	void Lock();
};

extern AccountManager GAccountManager;
