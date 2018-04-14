#include "CManager.h"



CManager::CManager(Database *DBO_Ptr, MessageHandler *MHO_Ptr,Socket *SO_Ptr)
{
	
	DBO_M = DBO_Ptr;
	MHO_M = MHO_Ptr;
	SO_M = SO_Ptr;
	SO_M->StartLoop();
}


CManager::~CManager()
{
}
