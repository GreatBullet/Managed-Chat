#include"CManager.h"
#include"Socket.h"
#include"Database.h"
#include"MessageHandler.h"
int main()
{
	Database *DatabaseObject = new Database;
	MessageHandler* MessageHandlerObject = new MessageHandler;
	Socket *SocketObject = new Socket;
	CManager ManageObject(DatabaseObject,MessageHandlerObject,SocketObject);
	StorageProgramSource source = DatabaseObject->ParseStorage("Res/Message.storage");
	std::cout << source.IndexSource;
	std::cin.get();
	delete SocketObject;
	delete MessageHandlerObject;
	delete DatabaseObject;
	return 0;
}