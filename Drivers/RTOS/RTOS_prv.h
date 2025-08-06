/*
 * RTOS_prv.h
 *
 *  Created on: Aug 6, 2025
 *      Author: Nada Mamdouh
 */

#ifndef RTOS_RTOS_PRV_H_
#define RTOS_RTOS_PRV_H_

typedef enum
{
	Suspended,
	Running

}TaskState;

typedef struct{
	void (*TaskFunction)(void);
	u16 Periodicity;
	u8 FirstDelay;
	TaskState TaskRunningState;
}Task_t;


#define OUT_OF_RANGE		1
#define PRIORITY_COLLISION	2
#define NO_TASK_EXISTS		3

#endif /* RTOS_RTOS_PRV_H_ */
