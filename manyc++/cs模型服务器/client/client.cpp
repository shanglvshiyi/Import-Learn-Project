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
		std::cout << "socket func error, error num is : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return false;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port=htons(port);
	inet_pton(AF_INET, ip, &servAddr.sin_addr.S_un.S_addr);
	//������������
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
	assert(servSock != INVALID_SOCKET);//����������ȷ�ģ�������Ƿ��ش���
	return true;
}
bool Client::recvRet()
{
	recvLen = recv(servSock, recvBuf, 128, 0);
	if (recvLen == 0)
	{
		std::cout << "�ͻ������ŵĶϿ�����" << std::endl;
	}
	if (recvLen < 0)
	{
		int errorNum = WSAGetLastError();
		if (errorNum == 10054)
		{
			std::cout << "�ͻ���ǿ�ƵĶϿ�����" << std::endl;
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