#include<iostream>
#include<thread>
#include<mutex>//ʹ������ͷ�ļ�
//�����������̶߳Թ������ݾ����ж���������ȫ����������ݰ�ȫ���⡣
//�����������̶߳Թ������ݾ�����д��������������ݰ�ȫ���⣬��Ҫ���ݱ�����
//�����������̶߳Թ��������еĽ��ж����еĽ���д��Ҳ��������ݰ�ȫ���⣬��Ҫ�������ݱ�����
unsigned num = 0;
std::mutex myMutex1;
std::mutex myMutex2;
void test()
{
	//myMutex.lock();//�������÷��������������߳�˭��ִ�е�lock˭����ס����ִ�еľͻ�ͣ��
	for (unsigned i = 0; i < 10000000; ++i)
	{
		//lock_guard������һ����Χ��
		//������Ӱ������Ч������Ҫ�������Ǿ���С�ķ�Χ
		std::lock(myMutex1, myMutex2);
	    std::lock_guard<std::mutex>lg2(myMutex1,std::adopt_lock);//����д���������Է�ֹ���µڶ�����������Ժ�����д
		/*
		����������һ�γ���
		
		�����һ���߳�Ҳ����������˳�������������һ���ͻ����������bug,��std::lock(��1����2)���Ա��������������ֳ��ֿ�������
		���������������std::adopt_lock,��ʾ�������ֻ�п������ܾͲ�������������ͷŵ�������
		*/
		std::lock_guard<std::mutex>lg2(myMutex2,std::adopt_lock);
		/*
		����������һ�γ���


		*/
		num++;
	}
	//myMutex.unlock();//�������ִ�еĲŻ������������ʱ�����ִ�в�������,�������ǽ��������ԾͲ�Ҫ��lock��unlock��
}
int main()
{
	std::thread myThread(test);
	std::thread myThread2(test);
	myThread2.join();
	myThread.join();
    std::cout << num << std::endl;		
	return 0;
}