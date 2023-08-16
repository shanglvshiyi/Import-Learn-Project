#include <iostream>
#include <sys/types.h>
#include <dirent.h>
// 对目录的操作
unsigned tabNum = 0;
void readDir(const std::string &dirName)
{
    DIR *dir = opendir(dirName.c_str()); // 返回char指针
    if (!dir)
    {
        perror("opendir error 10");
        return;
    }
    // 读目录
    dirent *pDirent = nullptr;
    int oldErrorNum = errno; // 检查出错
    while (pDirent = readdir(dir))
    {
        const std::string &fileName = pDirent->d_name;
        if (fileName == "." || fileName == "..") // 不显示 .. 和 .
        {
            continue;
        }
        if (pDirent->d_type == DT_DIR) // d_type是获取目录的类型的 DT_DIR为目录类型DT_其他类型可以百度
        {
            for (unsigned i = 0; i < tabNum; i++)
            {
                std::cout << "\t"; // 给子目录文件加制表符
            }
            std::cout << "dir name is : " << fileName << std::endl;
            const std::string childDirName = dirName + "/" + fileName;
            tabNum++;
            readDir(childDirName); // 通过递归获取子目录文件夹
            tabNum--;
        }
        else
        {
            for (unsigned i = 0; i < tabNum; i++)
            {
                std::cout << "\t"; // 给子目录文件加制表符
            }
            std::cout << "file name is : " << fileName << std::endl;
        }
    }
    if (oldErrorNum != errno)
    {
        perror("readdir error");
        return;
    }
    closedir(dir); // 关闭目录
}
int main()
{
    readDir("./");
    return 0;
}