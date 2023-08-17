#include"memoryMgr.h"
#include<iostream>
#include<assert.h>
MemoryAlloc::MemoryAlloc(unsigned unitcount_, unsigned unitsize_):unitcount(unitcount_),unitsize(unitsize_),
pMemoryAlloc(nullptr),pBlockHeader(nullptr)
{
	initMemoryAlloc();
}
MemoryAlloc::~MemoryAlloc()
{
	if (pMemoryAlloc)
		free(pMemoryAlloc);
}
void MemoryAlloc::initMemoryAlloc()
{
	assert(pMemoryAlloc == nullptr);
	pMemoryAlloc = (char*)malloc(unitcount * (unitsize + sizeof(MemoryBlock)));
	if (!pMemoryAlloc)
	{
		std::cout << "pMemoryAlloc 指针为空 malloc分配内存失败" << std::endl;
		return;
	}
	pBlockHeader = (MemoryBlock*)pMemoryAlloc;
	for (int i; i < unitcount; ++i)
	{
		//分别指向对应的头
		MemoryBlock* pMemoryBlock = (MemoryBlock*)(pMemoryAlloc + i * (unitsize + sizeof(MemoryBlock)));
		pMemoryBlock->pAlloc = this;
		if (i != unitcount)//指向下一条的头
			pMemoryBlock->pNext = (MemoryBlock*)(pMemoryAlloc + (i + 1) * (unitsize + sizeof(MemoryBlock)));
		else
			pMemoryBlock->pNext = nullptr;
	}
}
void* MemoryAlloc::allocMem(size_t nSize)
{
	if (pBlockHeader)
	{
		MemoryBlock* pMemoryBlcok = (MemoryBlock*)(char*)malloc(nSize + sizeof(MemoryBlock));
		pMemoryBlcok->pAlloc = nullptr;
		pMemoryBlcok->pNext = nullptr;
		return (char*)pMemoryBlcok + sizeof(MemoryBlock);
	}
	else
	{
		char* pReturn = ((char*)pBlockHeader + sizeof(MemoryBlock));
		pBlockHeader = pBlockHeader->pNext;
		return pReturn;
	}
}
void MemoryAlloc::freeMem(void* block)
{
	MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)block - sizeof(MemoryBlock));
	pMemoryBlock->pNext = pBlockHeader;
	pMemoryBlock = pBlockHeader;
}
MemoryMgr& MemoryMgr::getInstance()
{
	static MemoryMgr instance;
	return instance;
}
MemoryMgr::MemoryMgr() :memoryAlloc64(10, 64),
	memoryAlloc128(10, 128),
	memoryAlloc256(10, 256),
	memoryAlloc512(10, 512),
	memoryAlloc1024(10, 1024)
{
	
}
void* MemoryMgr::allocMem(size_t nSize)
{
	if (nSize < 1024)
	{
		unsigned i = 6;
		unsigned num = 32;
		while ((num=num*2)<nSize)
		{
			i++;
		}
		return memoryAllocMap[i].allocMem(nSize);
	}
	else
	{
		MemoryBlock* pMemoryBlock = (MemoryBlock*)(char*)malloc(nSize + sizeof(MemoryBlock));
		if (!pMemoryBlock)
		{
			pMemoryBlock = nullptr;
		}
		else
		{
			pMemoryBlock->pAlloc = nullptr;
			pMemoryBlock->pNext = nullptr;
			return pMemoryBlock+sizeof(MemoryBlock);
		}
	}
}
void  MemoryMgr::freeMem(void* block)
{
	MemoryBlock* pMemoryBlock = (MemoryBlock*)((char*)block - sizeof(MemoryBlock));
	if (!pMemoryBlock)
	{
		free(pMemoryBlock);
	}
	else
	{
		pMemoryBlock->pAlloc->freeMem(block);
	}
}