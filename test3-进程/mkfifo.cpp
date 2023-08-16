#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid > 0)
    {
        if (mkfifo("tem", 0644) == -1) // 创建一个临时管道文件名字是tem，这是命名管道
        {
            perror("mkfifo func error");
            return -1;
        }
        int inFifoFd = open("tem", O_WRONLY);
        if (inFifoFd == -1)
        {
            perror("open inFifoFd error");
            return -1;
        }
        const char *str = "hello world";
        if (write(inFifoFd, str, strlen(str)) == -1)
        {
            perror("write func error");
            return -1;
        }
        close(inFifoFd);
    }
    else
    {
        sleep(1);
        int outFifoFd = open("tem", O_RDONLY);
        if (outFifoFd == -1)
        {
            perror("open outFifoFd error");
            return -1;
        }
        char readBuf[32]{};
        if (read(outFifoFd, readBuf, 32) == -1)
        {
            perror("read func error");
            return -1;
        }
        std::cout << readBuf << std::endl;
        close(outFifoFd);
        if (unlink("tem") == -1) // 这个函数的作用是释放tem临时管道文件
        {
            perror("unlink func error");
            return -1;
        }
    }
}