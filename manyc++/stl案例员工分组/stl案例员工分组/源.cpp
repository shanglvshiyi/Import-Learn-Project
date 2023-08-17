#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
#define cehua 0
#define meishu 1
#define yanfa 2
class worker
{
public:
	string m_name;
	int m_wage;//工资
};
void createworker(vector<worker>& v)//创建员工
{
	string nameseed = "abcdefghij";
	for (int i = 0; i < 10; i++)
	{
		worker w;
		w.m_name = "员工";
		w.m_name += nameseed[i];
		w.m_wage = rand() % 10000 + 10000;//随机10000-19999
		//将员工放入容器中
		v.push_back(w);	
	}
	//测试
	//for (vector<worker>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	cout << "姓名:" << it->m_name << " 工资" << it->m_wage << endl;
	//}
}
void setgroup(vector<worker>& v, multimap<int, worker>& m)//员工分组
{
	for (vector<worker>::iterator it = v.begin(); it != v.end(); it++)
	{
		//产生随机部门编号
		int deptid = rand() % 3;//012
		//将员工插入到分组中
		//key为部门编号，value为具体员工
		m.insert(make_pair(deptid, *it));
	}
}
void showworkerbygroup(multimap<int, worker>& m)
{
	cout << "策划部门:" << endl;
	multimap<int, worker>::iterator pos = m.find(cehua);
	int count = m.count(cehua);//统计策划部门人数
	int index = 0;
	for (; pos!=m.end()&&index<count; pos++,index++)
	{
		cout << "姓名：" << pos->second.m_name << " 工资：" << pos->second.m_wage << endl;
	}
	cout << "------------------------" << endl;
	cout << "美术部门:" << endl;
	pos = m.find(meishu);
	count = m.count(meishu);//统计策划部门人数
	index = 0;
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "姓名：" << pos->second.m_name << " 工资：" << pos->second.m_wage << endl;
	}
	cout << "------------------------" << endl;
	cout << "美术部门:" << endl;
	pos = m.find(yanfa);
	count = m.count(yanfa);//统计策划部门人数
	index = 0;
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "姓名：" << pos->second.m_name << " 工资：" << pos->second.m_wage << endl;
	}
}
int main()
{
	vector<worker>vworker;
	multimap<int, worker>mworker;
	//创建员工
	createworker(vworker);
	//员工分组
	setgroup(vworker,mworker);
	//分组显示
	showworkerbygroup(mworker);
	system("pause");
	return 0;
}