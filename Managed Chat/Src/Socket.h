#pragma once
#include<WS2tcpip.h>
#include<string>
#include<iostream>
#include<sstream>
#include<fstream>
#include<time.h>

class Socket
{
public:
	Socket();
	~Socket();
	void StartLoop();
	void StoreMessageReceives(char buf[4096], SOCKET sock);
private:
	WSADATA wsData;
	WORD ver;
	SOCKET listening;
	sockaddr_in hint;
	fd_set master;
	bool running;
	std::string msg;
};

