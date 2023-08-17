#include<iostream>
#include<string>
#include<fstream>
int main()
{
	std::string fileName;//�ļ���
	std::string fileContent;//�ļ�����
	while (std::cin >> fileName, !std::cin.eof())
	{
		if (std::cin.bad())
		{
			throw std::runtime_error("cin�� cin is corrupted");
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
			std::cout << "�ļ��Ѵ��ڣ������� file is exist,please try again" << std::endl;
			continue;
		}
	}
	return 0;
}