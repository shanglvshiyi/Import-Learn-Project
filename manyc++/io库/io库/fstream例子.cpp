#include<iostream>
#include<string>
#include<fstream>
int main()
{
	std::string fileName;//文件名
	std::string fileContent;//文件内容
	while (std::cin >> fileName, !std::cin.eof())
	{
		if (std::cin.bad())
		{
			throw std::runtime_error("cin损坏 cin is corrupted");
		}
		std::ifstream ifs(fileName);
		if (ifs.is_open())
		{
			while (std::getline(ifs, fileContent))
			{
				std::cout << fileContent << std::endl;
			}
			if (ifs.bad())
			{
				throw std::runtime_error("ifs iscorruped");
			}
			ifs.close();
		}
		else
		{
			ifs.clear();
			ifs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "文件已存在，请重试 file is exist,please try again" << std::endl;
			continue;
		}
	}
	return 0;
}