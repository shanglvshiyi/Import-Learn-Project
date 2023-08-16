#include <iostream>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
int main()
{
    struct stat st
    {
    }; // 获取文件属性的对象
    int fd = open("num.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open num.txt error");
        return -1;
    }
    if (fstat(fd, &st) == -1)
    {
        perror("fstat func error");
        return -1;
    }
    char *mapAddr = nullptr;
    mapAddr = static_cast<char *>(mmap(nullptr, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)); // 参数看文档//SHARED是多个映射区共享一段内存
    // 用SHARED才能进行通信PRIVATE不行
    if (mapAddr == MAP_FAILED) // 这个是错误
    {
        perror("mmap func error");
        return -1;
    }
    close(fd);
    std::cout << mapAddr << std::endl;
    return 0;
}