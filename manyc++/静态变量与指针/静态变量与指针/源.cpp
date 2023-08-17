#include <iostream>
using namespace std;

int test()
{
    static int a = 0; // 静态变量在编译时就已经初始化了之后调用直接忽略这句
    return ++a;
}
int main()
{
    test();
    test();
    test();
    int a = test();
    cout << a << endl;
    int i = 20;
    int *pi = &i; //&i为i的地址,i存的是值,*pi存的是i的地址
    int &p = i;   // 引用只锁定指向内存的地址，不会修改内存，这句相当于int *const p=&i;
    return 0;
}