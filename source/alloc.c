// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

//Memory allocator

#include "alloc.h"

#define PAGE_SIZE 4Kb //defined in defines.h

void* initAlloc(void* allocBase, uint32_t reservedPages) {
	uint32_t physicalMemory = kernelGetPhysMem();
	void* memoryBase = kernelGetMemBase();
	nPages = physicalMemory / PAGE_SIZE;
	PageBasePointer = (PageDiscription*) allocBase;

	for (int i = 0; i < nPages; i++) pageBasePointer[i] = {memoryBase + (i * PAGE_SIZE), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF, PAGE_FREE | PAGE_FREEABLE};

	if (reservedPages > 0) {
		for (int i = 0; i < reservedPages; i++) pageBasePointer[i] = {memoryBase + (i * PAGE_SIZE), 0, i, 0, PAGE_RESERVED | PAGE_SUPERVISOR};
	}

	return (void*) allocBase + (nPages * sizeof(PageDiscription));
}
void* alloc(uint32_t size, uint16_t owner, PageFlags flags) {
	uint32_t pagesToAlloc = size / PAGE_SIZE;
	if (size % PAGE_SIZE > 0) pagesToAlloc++;
	void* memoryBase = kernelGetMemBase();

	uint32_t lastPage = 0;
	uint32_t rootPage = 0;
	for (int i = 0; i < nPages; i++) {
		if (PageBasePointer[i].flags & PAGE_FREE) { //free page found
			if (rootPage == 0) {
				PageBasePointer[i] = {memoryBase + (i * PAGE_SIZE), 0, i, owner, flags};
				lastPage = i;
				rootPage = i;
			} else {
				PageBasePointer[i] = {memoryBase + (i * PAGE_SIZE), 0, rootPage, owner, flags};
				PageBasePointer[lastPage].nextPage = i;
				lastPage = i;
			}
			pagesToAlloc--;
			if (pagesToAlloc == 0) break;
		}
	}

	if (pagesToAlloc > 0) {
		//not enough memory, alloc failed
		free(memoryBase + (rootPage * PAGE_SIZE), owner); //free what has been allready allocated
		return NULL;
	} else {
		return memoryBase + (rootPage * PAGE_SIZE));
	}
	kernelRecalcMMUMap(owner);
}
int free(void* base, uint16_t owner) {
	void* memoryBase = kernelGetMemBase();
	uint32_t basePage = (base - memoryBase) / PAGE_SIZE;
	uint32_t nextPageToClear = basePage;
	bool isSupervisor = kernelGetTaskInfo(owner).isSupervisor;

	while (42) {
		if (PageBasePointer[nextPageToClear].flags & PAGE_FREEABLE == 0) return 1; //page not freeable
		if (PageBasePointer[nextPageToClear].owner != owner && !isSupervisor) return 2; //cant excess page (not privileged)

		uint32_t tmp = PageBasePointer[nextPageToClear].nextPage;
		PageBasePointer[nextPageToClear] = {memoryBase + (nextPageToClear * PAGE_SIZE), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF, PAGE_FREE | PAGE_FREEABLE};
		nextPageToClear = tmp;
		if (nextPageToClear == 0 || nextPageToClear = 0xFFFFFFFF) break;
	}
	kernalRecalcMMUMap(owner);
	return 0;
}
int forceFree(void* base, uint16_t owner) {
	void* memoryBase = kernelGetMemBase();
	uint32_t basePage = (base - memoryBase) / PAGE_SIZE;
	uint32_t nextPageToClear = basePage;
	bool isSupervisor = kernelGetTaskInfo(owner).isSupervisor;

	if (!isSupervisor) return 1; //function is only for supervisor tasks

	while (42) {
		uint32_t tmp = PageBasePointer[nextPageToClear].nextPage;
		PageBasePointer[nextPageToClear] = {memoryBase + (nextPageToClear * PAGE_SIZE), 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFF, PAGE_FREE | PAGE_FREEABLE};
		nextPageToClear = tmp;
		if (nextPageToClear == 0 || nextPageToClear = 0xFFFFFFFF) break;
	}
	kernalRecalcMMUMap(owner);
	return 0;
};
