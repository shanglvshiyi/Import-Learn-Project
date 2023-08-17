#include <iostream>
#include <vector>
template <typename T>
class test
{
public:
    test(test &t)
    {
        date = {1, 2, 3, 4, 5};
    }
    ~test() {}
    T &operator[](const unsigned count) const
    {
        if (count >= date.size())
        {
            throw std::out_of_range("Test date is out range");
        }
        return date.at(count);
    }

private:
    std::vector<T> date;
};
template <typename T>
int main()
{
    test<int> t;
    unsigned count;
    std::cin >> count;
    try
    {
        std::cout << t[count] << std::endl;
    }
    catch (const std::out_of_range &except) // 越界类型错误
    {
        std::cout << except.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "exception occers,excpe is : unknow exception" << std::endl;
    }
}
