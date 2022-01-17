#pragma once
class PlayerManager
{
	USE_LOCK;

public:
	void Player_ThenAccount();
	void Lock();

};

extern PlayerManager GPlayerManager;
