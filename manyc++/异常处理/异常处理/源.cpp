// 异常处理案例被除数为0
#include <iostream>
#include <string>

int division(int divisor, int dividend)
{
    if (!dividend)
    {
        throw std::string("dividend is zero");
    }
    return divisor / dividend;
}
void cinNum(const std::string &str, int &num)
{
    std::cout << str << std::endl;
    while (std::cin >> num, !std::cin.eof())
    {
        if (std::cin.bad())
        {
            throw std::runtime_error("cin is corrupted");
        }
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "number format error,please input again" << std::endl;
        }
        break;
    }
}
int main()
{
    int divisor = 0;
    int dividend = 0;
    std::string str1 = "please input divisor";
    std::string str2 = "please input dividend";
    cinNum(str1, divisor);
    cinNum(str2, dividend);
    try // 用来保护程序
    {
        std::cout << division(divisor, dividend) << std::endl;
    }
    catch (const std::string &except) // 这里是吧division函数中抛出的异常打印//这里只能用char*
    {
        std::cout << "exception occers,except is : " << except << std::endl;
    }
    catch (...) // 三个点表示可以接收任何种类的异常
    {
        std::cout << "exception occers,except is : unknow exception" << std::endl;
    }
}