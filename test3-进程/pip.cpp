#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <cstring>
int main()
{
    // 管道是父进程关闭读文件子进程关闭写入段就可以达成管道，之间可以通信
    int pipeFD[2]{};
    if (pipe(pipeFD) == -1)
    {
        perror("pipe func error");
        return -1;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid > 0)
    {
        // 写入端
        close(pipeFD[0]); // 0是关闭读入
        const char *str = "hello world";
        if (write(pipeFD[1], str, strlen(str)) == -1)
        {
            perror("write func error");
            return -1;
        }
        close(pipeFD[1]);
    }
    else
    {
        // 读入端
        close(pipeFD[1]);
        char readBuf[32]{};
        if (read(pipeFD[0], readBuf, 32) == -1) // 此时的read是阻塞的，如果没有数据就会阻塞，父进程如果休眠一秒子进程就会延迟一秒输出
        {
            perror("read func error");
            return -1;
        }
        std::cout << readBuf << std::endl;
        close(pipeFD[0]);
    }
}