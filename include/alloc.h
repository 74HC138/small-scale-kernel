// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

#ifndef ALLOC_H
	#define ALLOC_H

	#include "kernel.h"
	#include "types.h"
	#include "defines.h"

	enum PageFlags {
		PAGE_FREE 	= (1 << 0),
		PAGE_RESERVED 	= (1 << 1),
		PAGE_FREEABLE	= (1 << 2),
		PAGE_SUPERVISOR	= (1 << 3),
	};

	struct PageDiscription {
		void* pageBase;		//4 Bytes
		uint32_t nextPage;	//4 Bytes
		uint32_t rootPage;	//4 Bytes
		uint16_t owner;		//2 Bytes
		PageFlags flags;	//2 Bytes
	};				//total 16 Bytes
	PageDiscription* PageBasePointer;
	uint32_t nPages;

	void* initAlloc(void* allocBase, uint32_t reservedPages);
	void* alloc(uint32_t size, uint16_t owner, PageFlags flags);
	int free(void* base, uint16_t owner);
	int forceFree(void* base, uint16_t owner);

#endif
