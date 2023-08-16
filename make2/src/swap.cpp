#include "swap.h"

void Swap::run()
{
    int temp;
    temp = _a;
    _a = _b;
    _b = temp;
    printInto();
}

void Swap::printInto()
{
    std::cout << "a=" << _a << std::endl;
    std::cout << "b=" << _b << std::endl;
}