#pragma once
void* operator new(size_t nsize);
void* operator new[](size_t nsize);
void operator delete(void* block);
void operator delete[](void* block);
//实现内存池需要重载new和delete函数 