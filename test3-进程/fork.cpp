#include <iostream>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    // exec是控制进程的
    else if (pid == 0) // pid==0是子进程
    {
        std::cout << "this is child process , child process id is : " << getpid() << std::endl;
        if (execl("/bin/ls", "ls", "-al", NULL) == -1) // exec+l是命令行,通过这些路径查找
        {
            perror("execl func error");
            return -1;
        }
        std::cout << std::endl;
        if (execlp("ls", "ls", "-al", NULL) == -1) // p是代表环境变量中的PATH，+p是如果是绝对路径那就查找，如果不是就通过环境变量查找
        {
            perror("execl func error");
            return -1;
        }
        char *perrArr[]{const_cast<char *>("ls"), const_cast<char *>("-al"), NULL};
        if (execvp("/bin/ls", perrArr) == -1) //+v就是数组的意思,v后加p与l后加p一样
        {
            perror("execl func error");
            return -1;
        }
        char *perArr[]{const_cast<char *>("A=1"), const_cast<char *>("B=2"), NULL}; // 定义环境变量
        if (execle("./fork", "fork", NULL, perArr) == -1)                           // e代表环境变量不能跟v使用
        {
            perror("execl func error");
            return -1;
        }
    }
    else // 其余情况是父进程
    {
        sleep(1);
        std::cout << pid << std::endl;
        std::cout << "this is parent process" << std::endl;
    }
}