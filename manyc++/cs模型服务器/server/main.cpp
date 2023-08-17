#include "server.h"
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
int main()
{
    Server server;
    // 绑定监听端口
    if (!server.start("192.168.249.1", 2345))
    {
        return -1;
    }
    // 接收请求
    if (!server.acceptClient())
    {
        return -1;
    }
    const char *msg = "hello world";
    // 发送函数
    if (!server.sendMsg(msg))
    {
        return -1;
    }
    // 接收函数
    if (!server.recvMsg())
    {
        return -1;
    }
    std::cout << server.getrecvBuf() << std::endl;
    system("pause");
    return 0;
}