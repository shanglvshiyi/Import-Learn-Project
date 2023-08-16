#pragma once
#include <iostream>

class Swap
{
public:
    Swap(int a, int b)
    {
        _a = a;
        _b = b;
    }
    void run();
    void printInto();

private:
    int _a;
    int _b;
};