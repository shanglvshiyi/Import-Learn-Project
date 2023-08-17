#include<iostream>
#include<algorithm>
#include<functional>
#include<vector>
using namespace std;
//for_each遍历算法的用法案例
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
	for_each(v.begin(), v.end(), print01);//也可以用仿函数，普通函数传函数命即可，仿函数要传函数对象，也就是带括号
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
void test02()//transform可以把一个容器拷贝到另一个容器
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int>v2;
	v2.resize(v.size());
	transform(v.begin(), v.end(),v2.begin(),Transform());
	for_each(v.begin(), v.end(), print01);//也可以用仿函数，普通函数传函数命即可，仿函数要传函数对象，也就是带括号
	cout << endl;
}
void test03()//find查找算法
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
void test04()//find_if查找算法-自定义数据类型
{
	person p1("aaa", 10);
	person p2("bbb", 150);
	vector<person>v;
	v.push_back(p1);
	v.push_back(p2);
	vector<person>::iterator it = find_if(v.begin(), v.end(),finds());
	cout << it->m_name <<"  " << it->m_age << endl;
}
void test05()//adjacent_find查找相邻位置重复算法
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
		cout << "没有找到相邻重复元素" << endl;
	}
	else
	{ 
	    cout <<"找到相邻重复元素:" << *it << endl;
	}
}
void test06()//binary_serch查找有序容器中是否有指定元素的算法
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	bool ret = binary_search(v.begin(), v.end(), 9);
	if (ret)
	{
		cout << "找到该元素" << endl;
	}
	else
	{
		cout << "未找到该元素" << endl;
	}
}
void test07()//count统计某一元素的出现的次数
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
	cout << "该元素出现了" << ct << "次" << endl;
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
	cout << "姓名：" << p.m_name << " 年龄：" << p.m_age << endl;
}
bool cmp(person& p,person &p4)
{
	return p.m_age > p4.m_age;
}
void test08()//count_if按照条件统计元素
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
	cout << "年龄大于二十的有" << count01<<"人"<<endl;
	sort(v.begin(), v.end(),cmp);
	for_each(v.begin(), v.end(), MyPrint);
}
void test09()//random_shuffle打乱顺序的算法
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
void test10()//merge算法将两个有序且顺序一样的容器合并到一个容器中
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
void test11()//reverse将容器反转
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
void test12()//copy拷贝算法
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
void test13()//replace将指定范围的旧数据替换
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
void test14()//replace_if按照条件将旧数据替换
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
void test15()//swap交换算法
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
//集合算法交集并集差集
void test16()
{
	vector<int>v1;
	vector<int>v2;
	vector<int>v3;//执行set_interction交集算法
	vector<int>v4;//执行set_union并集算法
	vector<int>v5;//执行set_difference差集算法
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i);
		v2.push_back(i+2);
	}
	//分别开辟空间
	v3.resize(min(v1.size(), v2.size()));
	v4.resize(v1.size() + v2.size());
	v5.resize(max(v1.size(), v2.size()));
	set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
	cout << "交集" << endl;
	for_each(v3.begin(), v3.end(), print01);
	cout << endl;
	set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v4.begin());
	cout << "并集" << endl;
	for_each(v4.begin(), v4.end(), print01);
	cout << endl;
	vector<int>::iterator itend = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v5.begin());//v1对v2的差集
	cout << "差集"<<endl;
	for_each(v5.begin(), itend, print01);
	cout << endl;
}
int main()
{
	test01();//for_each的用法案例
	test02();//transform算法案例
	test03();//find算法案例
	test04();//find_if算法案例
	test05();//adjacent_find算法案例
	test06();//binary_seach算法案例
	test07();//count算法案例
	test08();//count_if算法案例(中含有sort排序算法)
	test09();//random_shuffle算法案例
	test10();//merge算法案例
	test11();//reverse算法案例
	test12();//copy算法案例
	test13();//replace算法案例
	test14();//replace_if算法案例
	test15();//swap算法案例
	test16();//三种集合算法案例
	system("pause");
	return 0;
}