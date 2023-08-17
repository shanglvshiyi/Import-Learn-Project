#include<iostream>
#include<thread>
#include<mutex>//使用锁的头文件
//①至少两个线程对共享数据均进行读操作，完全不会出现数据安全问题。
//②至少两个线程对共享数据均进行写操作，会出现数据安全问题，需要数据保护。
//③至少两个线程对共享数据有的进行读，有的进行写，也会出现数据安全问题，需要进行数据保护。
unsigned num = 0;
std::mutex myMutex1;
std::mutex myMutex2;
void test()
{
	//myMutex.lock();//互斥锁用法，这里是两个线程谁先执行到lock谁就锁住，后执行的就会停下
	for (unsigned i = 0; i < 10000000; ++i)
	{
		//lock_guard作用在一个范围里
		//加锁会影响运行效率所以要让锁覆盖尽量小的范围
		std::lock(myMutex1, myMutex2);
	    std::lock_guard<std::mutex>lg2(myMutex1,std::adopt_lock);//这样写互斥锁可以防止以下第二条的情况，以后都这样写
		/*
		假如这里是一段程序
		
		如果另一个线程也有两个锁且顺序和这两个锁不一样就会出现死锁的bug,用std::lock(锁1，锁2)可以避免死锁，但是又出现开锁问题
		所以在所后面加上std::adopt_lock,表示让这个锁只有开锁功能就不会出现死锁和释放的问题了
		*/
		std::lock_guard<std::mutex>lg2(myMutex2,std::adopt_lock);
		/*
		假如这里是一段程序


		*/
		num++;
	}
	//myMutex.unlock();//开锁后后执行的才会继续，但是有时候可能执行不到这里,或者忘记解锁，所以就不要用lock和unlock了
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