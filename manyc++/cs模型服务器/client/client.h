#pragma once
#include<WinSock2.h>
class Client
{
public:
	Client();
	~Client();
	void close();
	bool init(const char* ip, unsigned short port);
	bool start(const char* ip, unsigned short port);
	bool recvRet();
	bool sendRet();
private:
	SOCKET servSock;
	char recvBuf[128]{};
	int recvLen = 0;
};
