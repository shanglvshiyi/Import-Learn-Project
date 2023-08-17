#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;
// 内建仿函数-算数仿函数
void test01()
{
    negate<int> n;
    // negate 一元仿函数取反仿函数
    cout << n(50) << endl;
    ;
    plus<int> p;
    cout << p(10, 20) << endl;
    // 二元仿函数 加法plus，此外还有减法minus,乘法multiplies,除法divides,取余modulus
}
class MyCompare
{
public:
    bool operator()(int v1, int v2)
    {
        return v1 > v2;
    }
};
// 内建仿函数-关系仿函数
// 最常用大于greater<int>(),可以修改排序规则，
void test02()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(30);
    v.push_back(40);
    v.push_back(20);
    v.push_back(50);
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
    // 降序
    sort(v.begin(), v.end(), greater<int>()); // 提供的内建仿函数
    for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}
// 逻辑仿函数 逻辑非logical
void test03()
{
    vector<bool> v;
    v.push_back(true);
    v.push_back(false);
    v.push_back(true);
    v.push_back(false);

    for (vector<bool>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
    // 利用逻辑非，将容器搬运到v2中，执行取反操作
    vector<bool> v2;
    v2.resize(v.size());
    transform(v.begin(), v.end(), v2.begin(), logical_not<bool>());
    for (vector<bool>::iterator it = v2.begin(); it != v2.end(); it++)
    {
        cout << *it << "  ";
    }
    cout << endl;
}
int main()
{
    test01();
    test02();
    test03();
    system("pause");
    return 0;
}