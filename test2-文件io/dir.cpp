#include <iostream>
#include <sys/types.h>
#include <dirent.h>
// 对目录的操作
int main()
{
    DIR *dir = opendir("./");
    if (!dir)
    {
        perror("opendir error 10");
        return -1;
    }
    // 读目录
    dirent *pDirent = nullptr;
    int oldErrorNum = errno; // 检查出错
    while (pDirent = readdir(dir))
    {
        std::cout << pDirent->d_name << std::endl;
    }
    if (oldErrorNum != errno)
    {
        perror("readdir error");
        return -1;
    }
    closedir(dir); // 关闭目录
    return 0;
}