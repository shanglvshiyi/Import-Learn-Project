#include<iostream>
#include<string>
//����ҵ�������л���Ҫ��bed������д���
//ֻ����bad����Ϊstring�ǲ����ܳ��ָ�ʽ�����
int mian()
{
	std::string str;
	while (std::getline(std::cin, str), !std::cin.eof())
	{
		if (std::cin.bad())
		{
			throw std::runtime_error("����ʱ�쳣");
		}
	}
	return 0;
}