#include<iostream>
using namespace std;
class Spear
{
protected:
	string name_;
	int age_;
public:
	Spear(const string& name, const int& age):name_(name), age_(age) {};//���캯��
	virtual~Spear(){};
};
class HandSpear:public Spear
{
protected:
	int bullet_;
public:
	HandSpear(const int& bullet):Spear(name_,age_),bullet_(bullet){}//�����๹�캯��
};
int main()
{
	Spear* pSpear = new HandSpear(18);//����ָ��ָ���������
	cout << typeid(*pSpear).name() << endl;//typeid�����е�name()�������Է��غ�������ʵ����typeidʹ�ø��������������麯�����������жϳ���
	if (string(typeid(*pSpear).name()) == "class HandSpear")
	{
		HandSpear* pHandSpear = dynamic_cast<HandSpear*>(pSpear);//dynamic_cast�ǽ�����ָ��ת��Ϊ����ָ��ĺ���
		if (pSpear)
		{
			cout << "success" << endl;
		}
	}
	delete pSpear;
	return 0;
}