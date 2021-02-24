// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

#ifndef KERNEL_H
	#define KERNEL_H

	#include "types.h"
	#include "defines.h" //check
	#include "platform.h"
	#include "task.h"
	#include "mmu.h"
	#include "alloc.h" //check
	#include "io.h"
	#include "driver.h"
	#include "fs.h"


	struct TaskInfo {
		uint16_t taskID;
		bool isSupervisor;
		char* taskName;
	};
	struct DeepTaskInfo { 	//only for supervisor
		uint16_t taskID;
		bool isSupervisor;
		char* taskName;
		//deep info
		REGISTERS* lastRegisterCache;
		MMUTranslateTable* MMUMap;
	};
	struct Version {
		uint16_t version;
		uint16_t subversion;
	};
	struct SystemInfo {
		uint32_t MemorySize;
		void* MemoryBase;
		char* launchArgs;
		Version kernelVersion;
	};

	void kernelInit(char* launchArgs); //kernel entry point (here the magic beginns)


	TaskInfo kernelGetTaskInfo(uint16_t taskID);
	void* kernelGetMemBase();
	uint32_t kernelGetPhysMemory();
	SystemInfo kernelGetSysInfo();


#endif
