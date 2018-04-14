#include "Socket.h"


Socket::Socket()
{
	ver = MAKEWORD(2, 2);
	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		std::cerr << "Cant Initialize winsock! Quitting" << std::endl;
	}

	listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		std::cerr << "Cant create a socket! Quitting" << std::endl;
	}

	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	listen(listening, SOMAXCONN);

	FD_ZERO(&master);

	FD_SET(listening, &master);
}


Socket::~Socket()
{
	FD_CLR(listening, &master);
	closesocket(listening);
	msg = " Server is shutting down. Goodbye\r\n";
	while (master.fd_count > 0)
	{
		SOCKET sock = master.fd_array[0];
		send(sock, msg.c_str(), msg.size() + 1, 0);
		FD_CLR(sock, &master);
		closesocket(sock);
	}
	WSACleanup();
	system("PAUSE");
}

void Socket::StartLoop()
{
	running = true;
	while (running)
	{
		fd_set copy = master;
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);
		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == listening)
			{
				SOCKET client = accept(listening, nullptr, nullptr);
				FD_SET(client, &master);
				std::string wlcMSG = "Welcome to the Awesome Chat Server\n";
				send(client, wlcMSG.c_str(), wlcMSG.size() + 1, 0);
			}
			else
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				int bytesIn = recv(sock, buf, 4096, 0);
				if (bytesIn <= 0)
				{
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					//if (buf[0] == '\\')
					//{
					//	std::string cmd = std::string(buf, bytesIn);
					//	if (cmd == "\\quit")
					//	{
					//		running = false;
					//		break;
					//	}
					//	continue;
					//}
					StoreMessageReceives(buf);
					//for (unsigned int i = 0; i< master.fd_count; i++)
					//{
					//	SOCKET outSock = master.fd_array[i];
					//	//	if (outSock != listening && outSock != sock) <-- i love myself
					//	//{
					//	std::ostringstream ss;
					//	ss << "SOCKET #" << sock << ": " << buf << "\r\n";
					//	std::string strOut = ss.str();
					//	send(outSock, strOut.c_str(), strOut.size() + 1, 0);
					//	//}
					//}
				}
			}

		}
	}
}

void Socket::StoreMessageReceives(char buf[4096])
{
	std::string DataPrep((LPCTSTR)buf);
	std::fstream target("test.txt", std::ios::app);
	target << DataPrep << '\n';
	target.close();
}
