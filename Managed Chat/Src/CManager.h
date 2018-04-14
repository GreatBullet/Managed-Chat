#pragma once
#include"Database.h"
#include"MessageHandler.h"
#include"Socket.h"
#include<iostream>
class CManager
{
	Database *DBO_M = nullptr;
	MessageHandler *MHO_M = nullptr;
	Socket *SO_M = nullptr;
public:
	CManager(Database *DBO_Ptr,MessageHandler *MHO_Ptr,Socket *SO_Ptr);
	~CManager();
};

