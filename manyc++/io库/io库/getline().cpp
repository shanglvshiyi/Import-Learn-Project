#include<iostream>
#include<string>
//在企业级代码中还是要对bed情况进行处理
//只考虑bad是因为string是不可能出现格式错误的
int mian()
{
	std::string str;
	while (std::getline(std::cin, str), !std::cin.eof())
	{
		if (std::cin.bad())
		{
			throw std::runtime_error("运行时异常");
		}
	}
	return 0;
}