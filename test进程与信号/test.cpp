#include <iostream>
#include <unistd.h>
#include <signal.h>

void SIGUSR1_handle_func(int sign)
{
    // 设置新的信号集结构体
    sigset_t newSet, oldSet;
    // 对信号集进行清空
    sigemptyset(&newSet);
    // 把想要屏蔽的信号添加到信号集中
    sigaddset(&newSet, SIGUSR2);
    sigprocmask(SIG_BLOCK, &newSet, &oldSet);
    std::cout << "accept signal SIGUSR1 start" << std::endl;
    sleep(5);
    std::cout << "accept signal SIGUSR1 end" << std::endl;
    sigprocmask(SIG_BLOCK, nullptr, &oldSet);
}
void SIGUSR2_handle_func(int sign)
{
    std::cout << "accept signal SIGUSR2 start" << std::endl;
    sleep(5);
    std::cout << "accept signal SIGUSR2 end" << std::endl;
}
int main()
{
    signal(SIGUSR1, SIGUSR1_handle_func); // SIG_IGN是忽略处理，SIGKILL无法被忽略处理，signal函数第二个参数是处理信号
    signal(SIGUSR2, SIGUSR2_handle_func);
    while (1)
    {
        sleep(1);
    }
    return 0;
}