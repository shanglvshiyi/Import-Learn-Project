#include <WinSock2.h> //pton函数实现实在这个库中
#include <WS2tcpip.h> //但是pton函数声明是这个库
#include <iostream>
#pragma comment(lib, "ws2_32.lib")

int main()

{
    // 打开网络库
    WSADATA data{};
    if (WSAStartup(MAKEWORD(2, 2), &data) == SOCKET_ERROR)
    {
        std::cout << "WSAStartup func error,error num is : " << WSAGetLastError() << std::endl;
        return -1;
    }
    // 参数分别是协议族，类型，指定协议
    SOCKET servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (servSock == INVALID_SOCKET)
    {
        std::cout << "socket func error,error num is : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return -1;
    }
    // 用sockaddr_in来初始化bind函数中的第二个参数
    sockaddr_in servAddr;
    servAddr.sin_family = AF_INET;
    // htons是将16位的内存转化为网络字节序 是 htons to net shot的简写
    servAddr.sin_port = htons(2345);
    // htonl是将32为的内存转化为网络字节序 后面是long 但是有安全隐患
    // pton函数可以安全的将32位内存转化为网络字节序
    inet_pton(AF_INET, "192.168.249.1", &servAddr.sin_addr.S_un.S_addr);
    // 第一个参数即socket描述字，第二个参数sockaddr*指向绑定的sockfd的地址，第三参数是地址长度 //绑定套接字和端口
    if (bind(servSock, (sockaddr *)&servAddr, sizeof(sockaddr)) == SOCKET_ERROR)
    {
        std::cout << "bind func error , error num is : " << WSAGetLastError() << std::endl;
        closesocket(servSock);
        WSACleanup();
        return -1;
    }
    if (listen(servSock, 193) == -1) // 监听
    {
        std::cout << "listen func error , error num is : " << WSAGetLastError();
        closesocket(servSock);
        WSACleanup();
        return -1;
    }
    SOCKET clnSock = accept(servSock, nullptr, nullptr); // 接收请求 用第一个协议站接受客户端
    if (clnSock == INVALID_SOCKET)
    {
        std::cout << "accept func error , error num is : " << WSAGetLastError() << std::endl;
        closesocket(servSock);
        WSACleanup();
        return -1;
    }
    const char *str = "hello world";
    char recvBuf[128]{};                        // 自己定义的缓冲区
    if (send(clnSock, str, strlen(str), 0) < 0) // 发送函数 发送方式接收方式为0
    {
        std::cout << "send func error, error num is : " << WSAGetLastError() << std::endl;
        closesocket(servSock);
        closesocket(clnSock);
        WSACleanup();
        return -1;
    }
    int recvRet = recv(clnSock, recvBuf, 128, 0); // 接收函数
    if (recvRet == 0)
    {
        std::cout << "client drop the connection gracefully 客户端优雅的断开连接" << std::endl;
    }
    if (recvRet < 0)
    {
        int errorNum = WSAGetLastError();
        if (errorNum == 10054)
        {
            std::cout << "client drop the connection coerce客户端强制断开连接" << std::endl;
        }
        else
        {
            std::cout << "recv func error,error num is : " << WSAGetLastError() << std::endl;
            closesocket(servSock);
            closesocket(clnSock);
            WSACleanup();
            return -1;
        }
    }
    std::cout << recvBuf << " 你接收到了客户端发送的数据" << std::endl;

    // 文件模块，网络模块，进程模块，设备模块，内存模块
    closesocket(servSock); // 属于网络模块必须要关闭掉
    closesocket(clnSock);
    WSACleanup(); // 使用这个网络库需要网卡，属于设备模块也要关闭掉

    system("pause");
    return 0;
}