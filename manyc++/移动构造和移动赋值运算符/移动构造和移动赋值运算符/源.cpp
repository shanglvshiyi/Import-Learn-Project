#include <iostream>
using namespace std;
class Test
{
public:
    Test() = default; // 默认构造函数
    Test(const Test &test)
    {
        if (test.str_)
        {
            str_ = new char[strlen(test.str_) + 1];       // 分配内存strlen是获取字符串长度的但是不会取到最后一位所以要+1
            strcpy_s(str_, strlen(test.str_), test.str_); // strcopy_s是将右边的复制给左边的
        }
        else
        {
            str_ = nullptr;
        }
    }
    Test(Test &&test) // 移动构造函数不能加const，要不不能修改值
    {
        if (test.str_)
        {
            str_ = test.str_; // 移动构造可以直接转移权限
            test.str_ = nullptr;
        }
        else
        {
            str_ = nullptr; // 移动构造函数写起来效率高
        }
    }
    Test &operator=(const Test &test)
    {
        if (this == &test) // 判断是不是同一个对象
        {
            return *this;
        }
        if (str_)
        {
            delete[] str_;
            str_ = nullptr;
        }
        if (test.str_)
        {
            str_ = new char[strlen(test.str_) + 1];
            strcpy_s(str_, strlen(test.str_) + 1, test.str_);
        }
        else
        {
            str_ = nullptr;
        }
        return *this;
    }
    Test &operator=(Test &&test)
    {
        if (this == &test)
        {
            return *this;
        }
        if (str_)
        {
            delete[] str_;
            str_ = nullptr;
        }
        if (this->str_)
        {
            str_ = test.str_;
            test.str_ = nullptr;
        }
        else
        {
            str_ = nullptr;
        }
        return *this;
    }

private:
    char *str_ = nullptr; // nullptr代替null声明空指针
};
Test makeTest()
{
    Test t;
    return t;
}
int main()
{
    makeTest();
    return 0;
}