#include<iostream>
#include<fstream>
#include<string>
void outPutFileContent(const std::string& fileName)
{
	std::ifstream ifs(fileName);
	std::string fileContent;
	if (ifs.is_open())
	{
		while (ifs >> fileContent)
		{
			std::cout << fileContent << std::endl;
		}
		if (ifs.bad())
		{
			throw std::runtime_error("ifs is corrupted");
		}
		ifs.close();
	}
	else
	{
		if (ifs.bad())
		{
			throw std::string("ifs is corrupted");
		}
		if (ifs.fail())
		{
			throw std::string("file not exist");
		}
	}
}
int main()
{
	std::string fileName;
	std::cin >> fileName;
	try
	{
		outPutFileContent(fileName);
	}
	catch (const std::string& except)
	{
		std::cout << "exception occers,except is :" << except<<std::endl;
	}
	catch (...)
	{
		std::cout << "exception occers,except is : unkown exception" << std::endl;
	}
}