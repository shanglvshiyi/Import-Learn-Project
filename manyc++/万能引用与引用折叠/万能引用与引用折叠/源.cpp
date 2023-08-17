#include<iostream>
#include<boost\type_index.hpp>
using boost::typeindex::type_id_with_cvr;//用这个获取类型
template<typename T>//在类中写需要把这行与函数捆绑住
void test(T&& elem)//第一种万能引用的写法模板型
{
	std::cout <<"elem type is : " << type_id_with_cvr<decltype(elem)>().pretty_name() << std::endl;
	std::cout <<"T type is : " << type_id_with_cvr<T>().pretty_name() << std::endl;
}
int main()
{
	int i = 10;
	test(i);
	//第二种万能引用的写法auto型
	//万能引用不能加const
	auto&& elem = std::move(i);
	std::cout << type_id_with_cvr<decltype(elem)>().pretty_name() << std::endl;
	return 0;
}

