#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<list>
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

	SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (servSock == INVALID_SOCKET)
	{
		std::cout << "socket func num error,error num is : " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	sockaddr_in servAddr{};
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(2345);
	inet_pton(AF_INET, "192.168.249.1", &servAddr.sin_addr.S_un.S_addr);
	if (bind(servSock, (sockaddr*)&servAddr, sizeof(sockaddr)) == SOCKET_ERROR)
	{
		std::cout << "bind func error,error num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return 1;
	}

	if (listen(servSock, 128) == SOCKET_ERROR)
	{
		std::cout << "listen func error,eror num is : " << WSAGetLastError() << std::endl;
		closesocket(servSock);
		WSACleanup();
		return 1;
	}

	std::list<SOCKET>clntlist;
	while (1)
	{
		fd_set fdRead;
		FD_ZERO(&fdRead);
		FD_SET(servSock, &fdRead);
		for (auto clntSock : clntlist)
		{
			FD_SET(clntSock, &fdRead);
		}
		timeval tv{ 1,0 };
		int selectRet = select(0, &fdRead, nullptr, nullptr, &tv);
		if (selectRet > 0)
		{
			for (unsigned i = 0; i < fdRead.fd_count; ++i)
			{
				if (fdRead.fd_array[i] == servSock)
				{
					SOCKET clntSock = accept(servSock, nullptr, nullptr);
					if (clntSock == INVALID_SOCKET)
					{
						std::cout << "accept func error,error num is : " << WSAGetLastError() << std::endl;
						break;
					}
					clntlist.push_back(clntSock);
				}
				else
				{
					Header header;
					int recvRet = recv(fdRead.fd_array[i], (char*)&header, sizeof(Header), 0);
					if (recvRet <= 0)
					{
						std::cout << "recv func error,error num is : " << WSAGetLastError() << std::endl;
						closesocket(servSock);
						for (auto client : clntlist)
							closesocket(client);
						WSACleanup();
						return 1;
					}
					switch (header.cmd)
					{
					case CMD::LOGIN:
					{	
						Login login;
						int recvRet2 = recv(fdRead.fd_array[i], (char*)&login + sizeof(Header), sizeof(Login) - sizeof(Header), 0);
						if (recvRet2 <= 0)
						{
							std::cout << "recv func error,error num is : " << WSAGetLastError() << std::endl;
							closesocket(servSock);
							for (auto client : clntlist)
								closesocket(client);
							WSACleanup();
						}
						LoginResult loginResult(10);
						if (send(fdRead.fd_array[i], (char*)&loginResult, sizeof(LoginResult), 0) < 0)
						{
							std::cout << "send func error,error num is : " << WSAGetLastError() << std::endl;
							closesocket(servSock);
							for (auto client : clntlist)
								closesocket(client);
							WSACleanup();
							return 1;
						}
						break;
					}
					case CMD::LOGOUT:
					{
						Logout logout;
						int recvRet2 = recv(fdRead.fd_array[i], (char*)&logout + sizeof(Header), sizeof(Logout) - sizeof(Header), 0);
						if (recvRet2 <= 0)
						{
							std::cout << "recv func error,error num is : " << WSAGetLastError() << std::endl;
							closesocket(servSock);
							for (auto client : clntlist)
								closesocket(client);
							WSACleanup();
						}
						LogoutResult logoutResult(10);
						if (send(fdRead.fd_array[i], (char*)&logoutResult, sizeof(LogoutResult), 0) < 0)
						{
							std::cout << "send func error,error num is : " << WSAGetLastError() << std::endl;
							closesocket(servSock);
							for (auto client : clntlist)
								closesocket(client);
							WSACleanup();
							return 1;
						}
					}
					default:
						break;
					}
				}
			}
		}
		else if (selectRet == 0)
		{
			std::cout << "do something else" << std::endl;
			continue;
		}
		else
		{
			std::cout << "select func error,error num is:" << WSAGetLastError() << std::endl;
			break;
		}
	}
	closesocket(servSock);
	for (auto client : clntlist)
		closesocket(client);
	WSACleanup();
	system("pause");
	return 0;
}