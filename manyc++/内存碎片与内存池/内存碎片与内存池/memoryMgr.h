#pragma once
#include<map>
const unsigned MAX_UNIT_SIZE = 1024;
class MemoryAlloc;
class MemoryBlock
{
public:
	MemoryBlock* pNext = nullptr;
	MemoryAlloc* pAlloc = nullptr;
};
class MemoryAlloc
{
public:
	MemoryAlloc(unsigned unitcount_, unsigned unitsize_);
	~MemoryAlloc();
	void initMemoryAlloc();
	void* allocMem(size_t nSize);
	void freeMem(void* block);
private:
	char* pMemoryAlloc;
	MemoryBlock* pBlockHeader;
	unsigned unitcount;
	unsigned unitsize; 
};
//µ¥ÀýÄ£Ê½
class MemoryMgr
{
public:
	static MemoryMgr& getInstance();
	MemoryMgr(const MemoryMgr& memoryMgr) = delete;
	MemoryMgr operator= (const MemoryMgr& memoryMgr) = delete;
	void* allocMem(size_t nsize);
	void freeMem(void* block);
	std::map<unsigned, MemoryAlloc>memoryAllocMap;
private:
	MemoryAlloc memoryAlloc64;
	MemoryAlloc memoryAlloc128;
	MemoryAlloc memoryAlloc256;
	MemoryAlloc memoryAlloc512;
	MemoryAlloc memoryAlloc1024;
	MemoryMgr();
};