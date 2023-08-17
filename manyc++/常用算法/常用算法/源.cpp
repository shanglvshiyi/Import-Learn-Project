#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;
//for_each�����㷨���÷�����
void print01(int val)
{
	cout << val << " ";
}
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	for_each(v.begin(), v.end(), print01);//Ҳ�����÷º�������ͨ���������������ɣ��º���Ҫ����������Ҳ���Ǵ�����
	cout << endl;
}
class Transform
{
public:
	int operator()(int v)
	{
		return v;
	}
};
void test02()//transform���԰�һ��������������һ������
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v2;
	v2.resize(v.size());
	transform(v.begin(), v.end(),v2.begin(),Transform());
	for_each(v.begin(), v.end(), print01);//Ҳ�����÷º�������ͨ���������������ɣ��º���Ҫ����������Ҳ���Ǵ�����
	cout << endl;
}
void test03()//find�����㷨
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>::iterator it=find(v.begin(), v.end(), 5);
	cout <<*it<< endl;
}


//find_if
class person
{
public:
	person(string name, int age)
	{
		this->m_name = name;
		this->m_age = age;
	}
	string m_name;
	int m_age;
};
class finds
{
public:
	bool operator()(person& p)
	{
		return p.m_age > 10;
	}
};
void test04()//find_if�����㷨-�Զ�����������
{
	person p1("aaa", 10);
	person p2("bbb", 150);
	vector<person>v;
	v.push_back(p1);
	v.push_back(p2);
	vector<person>::iterator it = find_if(v.begin(), v.end(),finds());
	cout << it->m_name <<"  " << it->m_age << endl;
}
void test05()//adjacent_find��������λ���ظ��㷨
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		if (i == 5)
		{
			v.push_back(i);
		}
	}
	vector<int>::iterator it = adjacent_find(v.begin(), v.end());
	if (it == v.end())
	{
		cout << "û���ҵ������ظ�Ԫ��" << endl;
	}
	else
	{ 
	    cout <<"�ҵ������ظ�Ԫ��:" << *it << endl;
	}
}
void test06()//binary_serch���������������Ƿ���ָ��Ԫ�ص��㷨
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	bool ret = binary_search(v.begin(), v.end(), 9);
	if (ret)
	{
		cout << "�ҵ���Ԫ��" << endl;
	}
	else
	{
		cout << "δ�ҵ���Ԫ��" << endl;
	}
}
void test07()//countͳ��ĳһԪ�صĳ��ֵĴ���
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		if(i==3)
		{
			v.push_back(i);
		}
	}
	int ct = count(v.begin(), v.end(), 3);
	cout << "��Ԫ�س�����" << ct << "��" << endl;
}
class Compear
{
public:
	bool operator()(const person &p)
	{
		return p.m_age > 20;
	}
};
void MyPrint(person &p)
{
	cout << "������" << p.m_name << " ���䣺" << p.m_age << endl;
}
bool cmp(person& p,person &p4)
{
	return p.m_age > p4.m_age;
}
void test08()//count_if��������ͳ��Ԫ��
{
	person p1("aaa", 10);
	person p2("bbb", 40);
	person p3("ccc", 50);
	person p4("ddd", 30);
	person p5("eee", 20);
	vector<person>v;
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);
	v.push_back(p4);
	v.push_back(p5);
	int count01 = count_if(v.begin(), v.end(), Compear());
	cout << "������ڶ�ʮ����" << count01<<"��"<<endl;
	sort(v.begin(), v.end(),cmp);
	for_each(v.begin(), v.end(), MyPrint);
}
void test09()//random_shuffle����˳����㷨
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		if (i == 3)
		{
			v.push_back(i);
		}
	}
	random_shuffle(v.begin(), v.end());
	for_each(v.begin(),v.end(),print01);
	cout << endl;
}
void test10()//merge�㷨������������˳��һ���������ϲ���һ��������
{
	vector<int>v;
	vector<int>v2;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		v2.push_back(i + 1);
	}
	vector<int>v3;
	v3.resize(v.size() + v2.size());
	merge(v.begin(), v.end(), v2.begin(), v2.end(),v3.begin());
	for_each(v3.begin(), v3.end(), print01);
	cout << endl;
}
void test11()//reverse��������ת
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	reverse(v.begin(), v.end());
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}
void test12()//copy�����㷨
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v2;
	v2.resize(v.size());
	copy(v.begin(), v.end(), v2.begin());
	for_each(v2.begin(), v2.end(), print01);
	cout << endl;
}
void test13()//replace��ָ����Χ�ľ������滻
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	replace(v.begin(), v.end(), 2, 200);
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}
int compr(int v1)
{
	return v1 > 3;
}
void test14()//replace_if�����������������滻
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	replace_if(v.begin(), v.end(),compr, 200);
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}
void test15()//swap�����㷨
{
	vector<int>v;
	vector<int>v2;
	for (int i = 0,j=10; i < 10; i++,j--)
	{
		v.push_back(i);
		v2.push_back(j);
	}
	swap(v, v2);
	for_each(v.begin(), v.end(), print01);
	cout << endl;
}
//�����㷨���������
void test16()
{
	vector<int>v1;
	vector<int>v2;
	vector<int>v3;//ִ��set_interction�����㷨
	vector<int>v4;//ִ��set_union�����㷨
	vector<int>v5;//ִ��set_difference��㷨
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i+2);
	}
	//�ֱ𿪱ٿռ�
	v3.resize(min(v1.size(), v2.size()));
	v4.resize(v1.size() + v2.size());
	v5.resize(max(v1.size(), v2.size()));
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "����" << endl;
	for_each(v3.begin(), v3.end(), print01);
	cout << endl;
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());
	cout << "����" << endl;
	for_each(v4.begin(), v4.end(), print01);
	cout << endl;
	vector<int>::iterator itend = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin());//v1��v2�Ĳ
	cout << "�"<<endl;
	for_each(v5.begin(), itend, print01);
	cout << endl;
}
int main()
{
	test01();//for_each���÷�����
	test02();//transform�㷨����
	test03();//find�㷨����
	test04();//find_if�㷨����
	test05();//adjacent_find�㷨����
	test06();//binary_seach�㷨����
	test07();//count�㷨����
	test08();//count_if�㷨����(�к���sort�����㷨)
	test09();//random_shuffle�㷨����
	test10();//merge�㷨����
	test11();//reverse�㷨����
	test12();//copy�㷨����
	test13();//replace�㷨����
	test14();//replace_if�㷨����
	test15();//swap�㷨����
	test16();//���ּ����㷨����
	system("pause");
	return 0;
}