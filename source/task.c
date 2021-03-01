// This source is part of the SSK project and thus is licensed under GPL-3.
// Use my code in any way you see fit and if you use it or parts of it please give creddit.
// Disclaimer: I dont provide any warranty that my code functions as intended.
// If my code causes trubbles and you loose all of your data and/or you computer catches fire thats on you!

#include "task.h"

void* initTask(void* taskBase, uint16_t maxTasks) {
	TaskBasePointer = (TaskInfo*) taskBase;
	nTasks = maxTasks;

	REGISTERS clearRegister = {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0};
	for (int i = 0; i < nTasks; i++) {
		TaskBasePointer[i] = {NULL, clearRegister, TASK_FREE, 0, NULL, NULL, i};
	}

	TaskLinkList = taskBase + (sizeof(TaskInfo) * nTasks);
	for (int i = 0; i < nTasks; i++) {
		TaskLinkList[i] = NULL;
	}

	return TaskLinkList + (sizeof(TaskInfo*) * nTasks);
}
void taskSwitch() {
	TaskInfo oldTask = *TaskLinkList[currentTask];
	currentTask++;
	if (currentTask >= nTasks) currentTask = 0;
	if (*TaskLinkList[currentTask] == NULL) currentTask = 0;

	TaskInfo newTask = *TaskLinkList[currentTask];

	oldTask.regStorage = getUserRegisters();
	setUserRegisters(newTask.regStorage);

	returnInt(); //return from interrupt
}
void taskSwitchTo(uint16_t taskID) {
	TaskInfo oldTask = *TaskLinkList[currentTask];
	currentTask++;
	if (currentTask >= nTasks) currentTask = 0;
	TaskInfo newTask = TaskBasePointer[taskID];

	oldTask.regStorage = getUserRegsiters();
	setUserRegisters(newTask.regStorage);

	returnInt(); //return from interrupt
}
int taskPurge(uint16_t taskID) {
	for (int i < nTasks; i++) {
		if (TaskLinkList[i]->taskID == taskID) TaskLinkList[i] == NULL;
	}
	TaskBasePointer[taskID] = {NULL, {0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0}, 0, 0}, TASK_FREE, 0, NULL, NULL, taskID};
	taskSort();
}
uint16_t taskCreate(uint32_t PC, uint32_t SP, uint32_t Param, char* taskName, TaskFlags taskFlags, TaskScopes taskScopes, uint16_t parent) {
	int freeTask;
	for (freeTask = 0; i < nTasks; i++) {
		if (TaskBasePointer[freeTask].taskFlags & TASK_FREE > 0) break;
	}
	if (freeTask >= nTasks - 1) return 0; //failed no free tasks
	TaskBasePointer[freeTask] = {taskName, {{0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, Param, SP}, PC, 0}, taskFlags, taskScopes, 0, 0, freeTask};
	if (parent > 0 && parent < nTasks) {
		if (TaskBasePointer[parent].child > 0) {
			TaskBasePointer[freeTask].nextChild = TaskBasePointer[parent].child;
			TaskBasePointer[parent].child = freeTask;
			TaskBasePointer[freeTask].child = 0;
		} else {
			TaskBasePointer[parent].child = freeTask;
			TaskBasePointer[freeTask].nextChild = 0;
			TaskBasePointer[freeTask].child = 0;
		}
	}
	return freeTask;
}
TaskInfo getTaskInfo(uint16_t taskID) {

}
int taskSuspend(uint16_t taskID) {

}
int taskResume(uint16_t taskID) {

}
int taskSort() {
	uint32_t changes = 0;
	while (42) {
		for (int i = 0; i < nTasks - 1; i++) {
			if (TaskLinkList[i] == NULL && TaskLinkList[i+1] != NULL) {
				TaskLinkList[i] = TaskLinkList[i+1];
				TaskLinkList[i+1] = NULL;
				changes++;
			}
		}
		if (changes == 0) break;
		changes = 0;
	}
	return 0;
}
int taskRemoveMultiple(uint16_t taskID) {

}
int taskClone(uint16_t taskID) {

}
int taskCloneCopy(uint16_t taskID) {

}
