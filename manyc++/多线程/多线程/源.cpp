#include <iostream>
#include <string>
#include <thread> //使用多线程必须包含的头文件
class Test
{
public:
    Test(int i_) : i(i_)
    {
        std::cout << std::this_thread::get_id() << std::endl;
    }
    Test(Test &t) : i(t.i)
    {
        std::cout << "Test(const Test& t)" << std::endl; // 如果test1使用值传递会调用两次两次赋值构造函数，所以要用引用传递
    }
    int i;
};
void test(int i, const std::string &str, const int *j)
{
    std::cout << "yoThread test" << std::endl;
}
void test1(Test &t) // 使用类对象要传引用不要传值
{
    std::cout << "child thread id is" << std::endl;
    t.i = 200;
}
int main()
{
    std::thread myThread([]()
                         { std::cout << "hellow word" << std::endl; }); // 创建子线程用thread类就行，括号里面必须是可调用对象
    myThread.join();                                                    // join的作用是有些子线程负责数据处理，如果主线程执行到这里就会检查子线程处理完毕，如果没有就会等待子线程处理
    /*myThread.detach();*/
    /*有些子线程和主线程完全分离，各自执行各自的。但主线程执行完毕，子线程就会立马被强制结束，容易导致各种bug于是deatch函数就诞生了。*/
    // detach()函数可以让子线程被C++运行库接管，就算主线程执行完毕，子线程也会由C++运行时库清理相关资源。保证不会出现各种意想不到的bug
    int i = 100;
    // hello 存在隐式转化std::string str="hello";很有可能主线程执行完毕隐式转化没有执行完毕,所以使用detach时，不要使用隐式类型转化
    std::thread yoThread(test, i, "hellow", &i); // 传递线程参数,可以传值传引用传指针
    yoThread.join();                             // 如果用detach（）最好不要传递指针，因为如果主线程执行完毕会导致指针地址回收，会让子线程去使用已经回收的数据
    Test t(100);
    std::thread yyThread(test1, std::ref(t)); // std::ref()可以不在调用复制构造函数然后就可以修改i的值
    yyThread.join();                          // 如果用death子线程和主线程分离会先输出100更改不了i值，用join会等子线程运行完
    std::cout << t.i << std::endl;
    // 当我们使用子线程函数时普通类型直接传值，类类型直接传引用
    return 0;
}