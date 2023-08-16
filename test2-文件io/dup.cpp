#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
int main()
{
    int fd = open("num2.txt", O_WRONLY | O_CREAT | O_APPEND);
    if (fd == -1)
    {
        perror("open file is error");
        return -1;
    }
    int oldFd = dup(STDOUT_FILENO); // 给标准输出重命名
    // dup是给fd创建别名和将可使用的文件描述符挑出最小的作为fd别名，本质也是一个对象,必须close掉
    // 操作fd和操作newfd是一模一样的
    if (oldFd == -1)
    {
        perror("dup func error");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        std::string errstr = std::string("dup2 func error , line name is : ") + std::to_string(__LINE__) + " file name is " + __FILE__;
        perror(errstr.c_str());
        return -1;
    }
    const char *str = "hello word\n";
    if (write(STDOUT_FILENO, str, strlen(str)) == -1)
    {
        std::string errstr = std::string("write func error , line name is : ") + std::to_string(__LINE__) + " file name is " + __FILE__;
        perror(errstr.c_str());
        return -1;
    }
    if (write(STDOUT_FILENO, "\n", 1) == -1)
    {
        std::string errstr = std::string("write func error , line name is : ") + std::to_string(__LINE__) + " file name is " + __FILE__;
        perror(errstr.c_str());
        return -1;
    }
    if (dup2(oldFd, STDOUT_FILENO) == -1) // dup与dup2配合使用防止函数重载,这里把dup2改回别名
    {
        // 这里报错与上边重复可以加行号
        std::string errstr = std::string("dup2 func error , line name is : ") + std::to_string(__LINE__) + "file name is " + __FILE__;
        perror(errstr.c_str());
        return -1;
    }
    close(oldFd);
    close(fd);
    return 0;
}