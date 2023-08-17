#include"server.h"
#include<iostream>
#include<WS2tcpip.h>
#include<cassert>
Server::Server():servSock(INVALID_SOCKET),clntSock(INVALID_SOCKET)
{}
Server::~Server()
{
	close();
}
void Server::close()
{
	if (servSock != INVALID_SOCKET)
	{
		closesocket(servSock);
		if(clntSock!=INVALID_SOCKET)
		{ 
			closesocket(clntSock);
		}
		WSACleanup();
		servSock = INVALID_SOCKET;
		clntSock = INVALID_SOCKET;
	}
}
bool Server::init(const char* ip, unsigned short port)
{
	//�������
	WSADATA data{};
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR)
	{
		std::cout << "WSAStartup func error,error num is : " << WSAGetLastError() << std::endl;
		return false;
	}
	//�����׽���
	servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET)
	{
		std::cout << "socket func error,error num is : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	//���׽��ֺͶ˿�
	if (bind(servSock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "bind func error ,error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return false;
	}
	//�����ö˿ں�
	if (listen(servSock, 193) == -1)
	{
		std::cout << "listen func error ,error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return false;
	}
}
bool Server::start(const char* ip, unsigned short port)
{
	init(ip, port);
	assert(servSock !=INVALID_SOCKET);
	return true;
}
bool Server::acceptClient()//��������
{
	clntSock = accept(servSock, nullptr, nullptr);
	if (clntSock == INVALID_SOCKET)
	{
		std::cout << "accept func error ,error num is : " << WSAGetLastError() << std::endl;
		return false;
	}
}
bool Server::sendMsg(const char* message)//���ͺ���
{
	if (send(clntSock, message, strlen(message), 0) < 0)
	{
		std::cout << "send func error ,error num is :" << WSAGetLastError() << std::endl;
		return false;
	}
}
bool Server::recvMsg()
{
	int recvRet = recv(clntSock, recvBuf, 128, 0);
	if (recvRet == 0)
	{
		std::cout << "�ͻ������ŵĶϿ�����" << std::endl;
	}
	if (recvRet < 0)
	{
		int errorNum = WSAGetLastError();
		if (errorNum == 10054)
		{
			std::cout << "�ͻ���ǿ�ƶϿ�����" << std::endl;
		}
		else
		{
			std::cout << "recv func error ,error num is : " << WSAGetLastError() << std::endl;
			return false;
		}
	}
}
const char* Server::getrecvBuf()
{
	return recvBuf;
}