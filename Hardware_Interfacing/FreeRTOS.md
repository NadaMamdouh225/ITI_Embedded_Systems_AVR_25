# Session: FreeRTOS
## Lab 1:
`Using FreeRTOS:` We have two tasks. First task blinks a LED every 200 msec and the other one
blinks a LED every 1000 msec.
The two tasks run in parallel.

### FreeRTOSConfig.h

```c
#define configCPU_CLOCK_HZ			( ( unsigned long ) 8000000 )
#define configTICK_RATE_HZ			( ( portTickType ) 1000 )  	// 1 OS tick each 1ms
#define configMAX_PRIORITIES		( ( unsigned portBASE_TYPE ) 4 ) // max 4 then priorities are (0, 1, 2, 3)
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 85 )
#define configTOTAL_HEAP_SIZE		( (size_t ) ( 1000 ) )
```
### main.c
```c
/*
 * main.c
 *
 *  Created on: Aug 4, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"


void Task_LED1(void *A_Pv)
{
	while(1)
	{
		MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
		vTaskDelay(200);
	}
}
void Task_LED2(void *A_Pv)
{
	while(1)
	{
		MDIO_vTogPinVal(DIO_PORTA, DIO_PIN1);
		vTaskDelay(1000);
	}

}




int main()
{

	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN1, DIO_OUTPUT);

	/* Create Task */
	xTaskCreate(Task_LED1,(signed const char * ) "LED1", 100,  NULL, 1, NULL);
	xTaskCreate(Task_LED2,(signed const char * ) "LED2", 100,  NULL, 3, NULL);

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0;
}


```
## Lab 2:
Using FreeRTOS:
Using FreeRTOS create Two TASKS:
1. Write on LCD "I am TASK 1" for 1 sec.
2. Write on LCD "I am TASK 2" for 1 sec.

### main.c : Solution without using semaphore
```c
/*
 * main.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"

void Task_LCD1(void *A_pv);
void Task_LCD2(void *A_pv);



int main()
{
	HLCD_vInit();

	/* Create Task */
	xTaskCreate(Task_LCD1,(signed const char * ) "LCD1", 100, NULL, 3, NULL);
	xTaskCreate(Task_LCD2,(signed const char * ) "LCD2", 100, NULL, 3, NULL);


	/* Start scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0;
}

void Task_LCD1(void *A_pv)
{
	while(1)
	{
//		HLCD_vClearScreen();
		HLCD_vDisplayString("Task1");
		vTaskDelay(1000);
	}

}
void Task_LCD2(void *A_pv)
{
	while(1)
	{
//		HLCD_vClearScreen();
		HLCD_vDisplayString("Task2");
		vTaskDelay(1000);
	}

}

```
