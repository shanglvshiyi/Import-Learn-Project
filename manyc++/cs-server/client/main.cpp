#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")
int main()
{
	WSADATA data{};
	if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR)
	{
		std::cout << "WSAStartup func is error, error num is : " << WSAGetLastError() << std::endl;
		return -1;
	}
	SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET)
	{
		std::cout << "socket func error , error num is : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(2345);
	inet_pton(AF_INET, "192.168.249.1", &servAddr.sin_addr.S_un.S_addr);
	if (connect(servSock, (sockaddr*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)//connect发送连接请求
	{
		std::cout << "connect func error, error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return -1;
	}
	char recvBuf[128]{};
	int reclen=recv(servSock, recvBuf, 128, 0);
	if (reclen == 0)
	{
		std::cout << "client drop the connection gracefully客户端优雅的断开连接" << std::endl;
	}
	if (reclen < 0)
	{
		int errorNum = WSAGetLastError();
		if (errorNum == 10054)
		{
			std::cout << "client dorp the connection coerce客户端强制断开连接" << std::endl;
		}
		else
		{
			std::cout << "recv func error, error num is : " << WSAGetLastError() << std::endl;
			closesocket(servSock);
			WSACleanup();
			return -1;
		}
	}
	if (send(servSock, recvBuf, reclen, 0) == SOCKET_ERROR)
	{
		std::cout << "send func error, error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return -1;
	}

	closesocket(servSock);
	WSACleanup();
}