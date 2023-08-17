// 在程序员重载了自己上面提到的C++编译器默认生成的函数之后，C++编译器将不在生成这些函数的默认形式。
// 但是C++允许我们使用 = default来要求编译器生成一个默认函数
#include <iostream>
using namespace std;
class MyClass
{
public:
    MyClass() = delete; // 相当于不能使用这个函数，也可以说不让系统默认生成这个函数
    MyClass() = default;
    ~MyClass();

private:
};
