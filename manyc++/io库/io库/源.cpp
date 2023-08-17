#include <iostream>
int main()
{
    int i = 10;
    // 以下代码很重要
    while (std::cin >> i, !std::cin.eof()) // 后表示没到文件结尾,逗号运算符先执行前面后执行后面
    {
        if (std::cin.bad())
        {
            throw std::runtime_error("运行时错误,cin损坏 cin is corrupted"); // 抛出异常
        }
        if (std::cin.fill()) // 如果发生错误
        {
            std::cin.clear();                                                   // 先清空状态栏
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 在忽略缓冲区,忽略到\n
            std::cout << "数据格式错误,请重试 date format error,please try again" << std::endl;
            continue;
        }
        std::cout << i << std::endl;
    }
    std::cout << "进程结束 process complete" << std::endl;
    return 0;
}