#include <iostream>
#include <vld.h>
using namespace std;
class B;
class A
{
public:
    weak_ptr<B> wr; // 就是为了处理shared_ptr循环引用设计的
};
class B
{
public:
    shared_ptr<A> sr;
};
void test(shared_ptr<int> pr)
{
}
int main()
{
    shared_ptr<int> pr = make_shared<int>(100); // shared_ptr共享性智能指针，用make_shared进行初始化
    cout << pr.use_count() << endl;
    cout << pr.unique() << endl
         << endl;            // unique判断该对象是否独占
    shared_ptr<int> pr1(pr); // 复制函数进行初始化，应和共享
    cout << pr.use_count() << endl;
    cout << pr.unique() << endl
         << endl;
    pr1.reset(); // reset函数无参数表示将对象置空，让堆内存的引用基数减一，带参数可以让对象指向new出的新的内存
    cout << pr.use_count() << endl;
    cout << pr.use_count() << endl;
    shared_ptr<int> pr2 = make_shared<int>(1000);
    pr.swap(pr2);                        // swap交换两个智能指针的内存
    shared_ptr<int> pr3(new int[100]()); // 智能指针创建数组的方法只有这一个
    cout << pr3.get()[10] << endl;       // 使用时只能用get函数
    test(pr2);                           // 智能指针传参直接值传递

    shared_ptr<A> sr1 = make_shared<A>();
    shared_ptr<B> sr2 = make_shared<B>();
    sr1->wr = sr2; // weak_ptr配合shared_ptr使用可以防止两个shared_ptr你指我我指你使内存泄露
    sr2->sr = sr1;

    unique_ptr<int> ur = make_unique<int>(100); // 一般推荐使用unique_ptr独占式智能指针,消耗更少,如果发现需要共享内存就用shared_ptr
    // 允许移动构造，移动赋值，相当于废弃ur
    unique_ptr<int> ur1(move(ur)); // 移动构造
    ur1 = move(ur);                // 移动赋值
    ur1.reset(new int(10));        // 不带参数直接释放，带参数释放后重新分配堆内存
    return 0;
}
void test02(unique_ptr<int> ur)
{
    shared_ptr<int> sr(move(ur)); // 将unique_ptr用move函数改为右值，可以转化为shared_ptr函数，代价是move函数里的ur不能在使用
}