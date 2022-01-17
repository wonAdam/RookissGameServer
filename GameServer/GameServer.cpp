#include "pch.h"
#include <iostream>
#include "CorePch.h"

#include "ThreadManager.h"

#include "AccountManager.h"
#include "PlayerManager.h"


int main()
{
	GThreadManager->Launch([=] 
		{
			while (true)
			{
				cout << "Player ThenAccount" << endl;
				GPlayerManager.Player_ThenAccount();
				this_thread::sleep_for(100ms);
			}
		});

	GThreadManager->Launch([=]
		{
			while (true)
			{
				cout << "Account ThenPlayer" << endl;
				GAccountManager.Account_ThenPlayer();
				this_thread::sleep_for(100ms);
			}
		});

	GThreadManager->Join();

	return 0;
}
