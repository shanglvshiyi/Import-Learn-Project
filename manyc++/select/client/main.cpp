#include<iostream>
#include<winsock2.h>
#include<WS2tcpip.h>
#include"message.hpp"
#pragma comment(lib,"ws2_32.lib")

int main()
{
	WSADATA data{};
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR)
	{
		std::cout << "WSAStartup func error,error num is : " << WSAGetLastError() << std::endl;
		return 1;
	}
	SOCKET servsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servsock == INVALID_SOCKET)
	{
		std::cout << "socket func error,error num is : " << WSAGetLastError() << std::endl;
		closesocket(servsock);
		WSACleanup();
		return 1;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(2345);
	inet_pton(AF_INET, "192.168.249.1",&servAddr.sin_addr.S_un.S_addr);
	if (connect(servsock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
	{
		std::cout << "connect func error,error num is:" << WSAGetLastError() << std::endl;
		closesocket(servsock);
		WSACleanup();
		return 1;
	}
	std::cout << "connection suscess" << std::endl;
	while (1)
	{
		Login login("aaa", "bbb");
		if (send(servsock, (char*)&login, sizeof(Login),0) < 0)
		{
			std::cout << "send func error,error num is: " << WSAGetLastError() << std::endl;
			break;
		}
		LoginResult loginResult;
		if (recv(servsock, (char*)&loginResult, sizeof(LoginResult), 0) <= 0)
		{
			std::cout << "recv func error,error num is:" << WSAGetLastError() << std::endl;
			break;
		}
		std::cout << loginResult.loginResultNum << std::endl;
		Sleep(1000);
	}
	system("pause");
	return 0;
}