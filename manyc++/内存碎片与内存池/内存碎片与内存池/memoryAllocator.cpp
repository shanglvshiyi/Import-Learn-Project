#include"memoryAllocator.h"
#include"memoryMgr.h"
void* operator new(size_t nsize)
{
	MemoryMgr::getInstance().allocMem(nsize);
}
void* operator new[](size_t nsize)
{
	MemoryMgr::getInstance().allocMem(nsize);
}
void operator delete(void* block)
{
	MemoryMgr::getInstance().freeMem(block);
}
void operator delete[](void* block)
{
	MemoryMgr::getInstance().freeMem(block);
}