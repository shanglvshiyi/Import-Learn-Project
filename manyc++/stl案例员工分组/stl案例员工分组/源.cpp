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
	int m_wage;//����
};
void createworker(vector<worker>& v)//����Ա��
{
	string nameseed = "abcdefghij";
	for (int i = 0; i < 10; i++)
	{
		worker w;
		w.m_name = "Ա��";
		w.m_name += nameseed[i];
		w.m_wage = rand() % 10000 + 10000;//���10000-19999
		//��Ա������������
		v.push_back(w);	
	}
	//����
	//for (vector<worker>::iterator it = v.begin(); it != v.end(); it++)
	//{
	//	cout << "����:" << it->m_name << " ����" << it->m_wage << endl;
	//}
}
void setgroup(vector<worker>& v, multimap<int, worker>& m)//Ա������
{
	for (vector<worker>::iterator it = v.begin(); it != v.end(); it++)
	{
		//����������ű��
		int deptid = rand() % 3;//012
		//��Ա�����뵽������
		//keyΪ���ű�ţ�valueΪ����Ա��
		m.insert(make_pair(deptid, *it));
	}
}
void showworkerbygroup(multimap<int, worker>& m)
{
	cout << "�߻�����:" << endl;
	multimap<int, worker>::iterator pos = m.find(cehua);
	int count = m.count(cehua);//ͳ�Ʋ߻���������
	int index = 0;
	for (; pos!=m.end()&&index<count; pos++,index++)
	{
		cout << "������" << pos->second.m_name << " ���ʣ�" << pos->second.m_wage << endl;
	}
	cout << "------------------------" << endl;
	cout << "��������:" << endl;
	pos = m.find(meishu);
	count = m.count(meishu);//ͳ�Ʋ߻���������
	index = 0;
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "������" << pos->second.m_name << " ���ʣ�" << pos->second.m_wage << endl;
	}
	cout << "------------------------" << endl;
	cout << "��������:" << endl;
	pos = m.find(yanfa);
	count = m.count(yanfa);//ͳ�Ʋ߻���������
	index = 0;
	for (; pos != m.end() && index < count; pos++, index++)
	{
		cout << "������" << pos->second.m_name << " ���ʣ�" << pos->second.m_wage << endl;
	}
}
int main()
{
	vector<worker>vworker;
	multimap<int, worker>mworker;
	//����Ա��
	createworker(vworker);
	//Ա������
	setgroup(vworker,mworker);
	//������ʾ
	showworkerbygroup(mworker);
	system("pause");
	return 0;
}