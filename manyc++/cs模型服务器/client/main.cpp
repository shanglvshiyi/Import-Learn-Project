#include"client.h"
#pragma comment(lib,"ws2_32.lib")
int main()
{
	Client cln;
	if (!cln.start("192.168.249.1", 2345))
	{
		return -1;
	}
	if (!cln.recvRet())
	{
		return -1;
	}
	if (!cln.sendRet())
	{
		return -1;
	}
	return 0;
}