#include <iostream>
int main()
{
    int i = 10;
    // ���´������Ҫ
    while (std::cin >> i, !std::cin.eof()) // ���ʾû���ļ���β,�����������ִ��ǰ���ִ�к���
    {
        if (std::cin.bad())
        {
            throw std::runtime_error("����ʱ����,cin�� cin is corrupted"); // �׳��쳣
        }
        if (std::cin.fill()) // �����������
        {
            std::cin.clear();                                                   // �����״̬��
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // �ں��Ի�����,���Ե�\n
            std::cout << "���ݸ�ʽ����,������ date format error,please try again" << std::endl;
            continue;
        }
        std::cout << i << std::endl;
    }
    std::cout << "���̽��� process complete" << std::endl;
    return 0;
}