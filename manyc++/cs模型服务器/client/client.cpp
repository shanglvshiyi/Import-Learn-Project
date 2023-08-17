#include"client.h"
#include<iostream>
#include<WS2tcpip.h>
#include<cassert>
Client::Client() :servSock(INVALID_SOCKET){}
Client::~Client()
{
	close();
}
void Client::close()
{
	if (servSock != INVALID_SOCKET)
	{
		closesocket(servSock);
		WSACleanup();
		servSock = INVALID_SOCKET;
	}
}
bool Client::init(const char* ip, unsigned short port)
{
	//打开网络库
	WSADATA data{};
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR)
	{
		std::cout << "WSAStartup func error,error num is : " << WSAGetLastError() << std::endl;
		return false;
	}
	//创建套接字
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET)
	{
		std::cout << "socket func error, error num is : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port=htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	//发送连接请求
	if (connect(servSock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "connect func error, error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return false;
	}
}
bool Client::start(const char* ip, unsigned short port)
{
	init(ip, port);
	assert(servSock != INVALID_SOCKET);//断言它是正确的，如果不是返回错误
	return true;
}
bool Client::recvRet()
{
	recvLen = recv(servSock, recvBuf, 128, 0);
	if (recvLen == 0)
	{
		std::cout << "客户端优雅的断开连接" << std::endl;
	}
	if (recvLen < 0)
	{
		int errorNum = WSAGetLastError();
		if (errorNum == 10054)
		{
			std::cout << "客户端强制的断开连接" << std::endl;
		}
		else
		{
			std::cout << "recv func error ,error num is : " << WSAGetLastError() << std::endl;
			return false;
		}
	}
}
bool Client::sendRet()
{
	if (send(servSock, recvBuf, 128, 0) == SOCKET_ERROR)
	{
		std::cout << "send func error: error num is : " << WSAGetLastError() << std::endl;
		return false;
	}
}