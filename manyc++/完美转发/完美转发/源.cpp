#include<iostream>
#include<boost\type_index.hpp>
using boost::typeindex::type_id_with_cvr;
template<typename T>
void func2(T&& elem);
template<typename T>
void func1(T&& elem)
{
	func2(std::forward<T>(elem));//forward<T>ģ����Խ������ת�����⣬����ת��Ҫ������������ʹ��
}
template<typename T>
void func2(T&& elem)
{
	std::cout << "elem type is : " << type_id_with_cvr<decltype(elem)>().pretty_name() << std::endl;
}
int main()
{
	int i = 10;
	func2(std::move(i));
	return 0;
}