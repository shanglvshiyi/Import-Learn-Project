#include <iostream>
#include <boost\type_index.hpp> //包含boost库中的功能
using boost::typeindex::type_id_with_cvr;
using namespace std;
int main()
{
    int i = 100;
    auto &i2 = i;                                                   // 要想auto推断出引用类型必须自己加引用符号
    cout << type_id_with_cvr<decltype(i2)>().pretty_name() << endl; // 可以打印类型
    const int &i0 = i;                                              // 2. auto关键字在推断引用的类型时：会直接将引用替换为引用指向的对象。
    // 其实引用一直是这样的，引用不是对象，任何使用引用的地方都可以直接替换成引用指向的对象。
    auto &i3 = i0; // 完全等于i3=i
    // auto关键字在推断类型时，如果没有引用符号，会忽略值类型的const修饰，而保留修饰指向对象的const，典型的就是指针。
    const int *const p1 = &i;
    auto p2 = p1;                                                   // 会忽略第二个const保留前面的，类型就是const int*加引用符号就会保留
    cout << type_id_with_cvr<decltype(p2)>().pretty_name() << endl; // 可以打印类型
    const int a = 100;
    auto a2 = a;                                                    // 因为传进的是值会忽略const加引用就会得到保留
    cout << type_id_with_cvr<decltype(a2)>().pretty_name() << endl; // 可以打印类型
    const int a3 = 100;
    auto &a4 = a3;
    cout << type_id_with_cvr<decltype(a4)>().pretty_name() << endl; // 可以打印类型
    return 0;
}