// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

#ifndef TASK_H
	#define TASK_H

	#include "types.h"
	#include "mmu.h"
	#include "platform.h"
	#include "kernel.h"

	enum TaskFlags {
		TASK_FREE = (1 << 0),
		TASK_SUPERVISOR = (1 << 1),
		TASK_TERMCHILD = (1 << 2)	//When set children of tasks that get terminated get terminated as well
	};
	enum TaskScopes {
		SCOPE_CREATETASK = (1 << 0),	//Scope to create new tasks
		SCOPE_READFS = (1 << 1),	//Scope to read filesystem
		SCOPE_ALLOCMEM = (1 << 2),	//Scope to allocate and free memory
		SCOPE_MODIFYFS = (1 << 3),	//Scope to modify filesystem (edit/delete)
		SCOPE_MOUNT = (1 << 4),		//Scope to mount and umount devices
		SCOPE_DRIVER = (1 << 5),	//Scope to add device drivers (dev drivers run as su [gives tasks basicly su acces])
		SCOPE_MODIFYVBR = (1 << 6),	//Scope to modify Vectortable (interrupts and syscalls)
		SCOPE_SILENT = (1 << 7)		//Scope to allow running in silent mode (in background without occupying a shell)
	};
	struct TaskInfo {
		char* taskName;
		REGISTERS regStorage;
		TaskFlags taskFlags;
		TaskScopes taskScopes;		//what the task and cant do
		uint16_t child;
		uint16_t nextChild;
		uint16_t taskID;
	};

	TaskInfo* TaskBasePointer;
	TaskInfo** TaskLinkList;
	uint16_t nTasks;
	uint16_t currentTask;

	void* initTask(void* taskBase, uint16_t maxTasks);
	void taskSwitch();
	void taskSwitchTo(uint16_t taskID);
	int taskPurge(uint16_t taskID);
	uint16_t taskCreate(void* PC, void* SP, void* Param, char* taskName, TaskFlags taskFlags, TaskScopes taskScopes, uint16_t parent);
	TaskInfo getTaskInfo(uint16_t taskID);
	int taskSuspend(uint16_t taskID); //task gets removed from task circulation (task can still be accesed via taskSwichTo)
	int taskResume(uint16_t taskID); //task gets readded to task circulation (can be added multiple times for more task time)
	int taskSort(); //sort task linkt list for optimal perfomance (multiple instaces of tasks get redistributet)
	int taskRemoveMultiple(uint16_t taskID); //removes multiple instances of tasks in circulation
	int taskClone(uint16_t taskID); //creates new task with its own memory space but with the same registers
	int taskCloneCopy(uint16_t taskID); //creates new tasks with its own memory space but with the same register and copys the memory space of the cloned task
	

#endif
