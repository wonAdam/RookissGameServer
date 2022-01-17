#include "pch.h"
#include "AccountManager.h"
#include "PlayerManager.h"

AccountManager GAccountManager;

void AccountManager::Account_ThenPlayer()
{
	WRITE_LOCK;
	GPlayerManager.Lock();
}

void AccountManager::Lock()
{
	WRITE_LOCK;
}