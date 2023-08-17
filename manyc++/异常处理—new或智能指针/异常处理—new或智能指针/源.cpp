#include<iostream>
#include<memory>
#include<vector>
int main()
{
	std::vector<std::unique_ptr<int>>unptr_int_vec;
	try
	{
		while (1)
		{
			std::unique_ptr<int>unique1(new int[100000000]());//=std::make_unique<int>(10);
			unptr_int_vec.push_back(std::move(unique1));
		}
	}
	catch (const std::bad_alloc& except)
	{
		std::cout << except.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "except occers,except is : " << "unkown exception" << std::endl;
	}
}