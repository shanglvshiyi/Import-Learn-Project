#include<iostream>
using namespace std;
class Spear
{
protected:
	string name_;
	int age_;
public:
	Spear(const string& name, const int& age):name_(name), age_(age) {};//构造函数
	virtual~Spear(){};
};
class HandSpear:public Spear
{
protected:
	int bullet_;
public:
	HandSpear(const int& bullet):Spear(name_,age_),bullet_(bullet){}//派生类构造函数
};
int main()
{
	Spear* pSpear = new HandSpear(18);//父类指针指向子类对象
	cout << typeid(*pSpear).name() << endl;//typeid函数中的name()函数可以返回函数的真实名称typeid使用父类或子类必须有虚函数否则类型判断出错
	if (string(typeid(*pSpear).name()) == "class HandSpear")
	{
		HandSpear* pHandSpear = dynamic_cast<HandSpear*>(pSpear);//dynamic_cast是将父类指针转化为子类指针的函数
		if (pSpear)
		{
			cout << "success" << endl;
		}
	}
	delete pSpear;
	return 0;
}