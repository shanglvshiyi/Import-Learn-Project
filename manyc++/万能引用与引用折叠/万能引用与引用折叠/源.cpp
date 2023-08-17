#include<iostream>
#include<boost\type_index.hpp>
using boost::typeindex::type_id_with_cvr;//�������ȡ����
template<typename T>//������д��Ҫ�������뺯������ס
void test(T&& elem)//��һ���������õ�д��ģ����
{
	std::cout <<"elem type is : " << type_id_with_cvr<decltype(elem)>().pretty_name() << std::endl;
	std::cout <<"T type is : " << type_id_with_cvr<T>().pretty_name() << std::endl;
}
int main()
{
	int i = 10;
	test(i);
	//�ڶ����������õ�д��auto��
	//�������ò��ܼ�const
	auto&& elem = std::move(i);
	std::cout << type_id_with_cvr<decltype(elem)>().pretty_name() << std::endl;
	return 0;
}

