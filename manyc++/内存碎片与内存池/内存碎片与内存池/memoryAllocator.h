#pragma once
void* operator new(size_t nsize);
void* operator new[](size_t nsize);
void operator delete(void* block);
void operator delete[](void* block);
//ʵ���ڴ����Ҫ����new��delete���� 