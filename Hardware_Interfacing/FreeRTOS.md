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
## Lab 2: Solution using semaphore
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
#include "../MCAL/ADC/ADC_int.h"
#include "../HAL/LCD/LCD_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"

xSemaphoreHandle LCD_semphr;

void Task_LCD1(void* pv);
void Task_LCD2(void* pv);

int main()
{

	HLCD_vInit();

	/* Create Task */
	xTaskCreate(Task_LCD1, NULL, 200,  NULL, 4, NULL);
	xTaskCreate(Task_LCD2, NULL, 200,  NULL, 3, NULL);

	/* Create Semaphore */
	vSemaphoreCreateBinary(LCD_semphr);

	/* Start Scheduler */
	vTaskStartScheduler();

	while(1)
	{

	}

	return 0;
}

void Task_LCD1(void* pv)
{
	while(1)
	{
		if(xSemaphoreTake(LCD_semphr, portMAX_DELAY) == pdTRUE)
		{
            //			HLCD_vClearScreen();
			HLCD_vDisplayString("Task1");
			xSemaphoreGive(LCD_semphr);
			vTaskDelay(1000);
		}
	}
}

void Task_LCD2(void* pv)
{
	while(1)
	{
		if(xSemaphoreTake(LCD_semphr, portMAX_DELAY) == pdTRUE)
		{
            //			HLCD_vClearScreen();
			HLCD_vDisplayString("Task2");
			xSemaphoreGive(LCD_semphr);
			vTaskDelay(1000);
		}
	}
}

```

## Lab 3:
We have two tasks that communicate with each other using a counting
semaphore:
1. A tactile switch is connected to external interrupts EXTO. When an ISR (Interrupt Service Routine) takes place,
it gives the semaphore.
2. Second Task: Waits for that semaphore and writes "button is pressed" on an LCD.

### EXTI Configuration
```c

#define EXTI_INT0         ENABLE
#define EXTI_INT0_SENSE_CTRL  EXTI_RISING

```
### main.c
```c
/*
 * main.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/EXTI/EXTI_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/semphr.h"

xSemaphoreHandle xSemaphore;
volatile u8 buttonPressedFlag = 0;

/* Function Prototypes */
void APP_EXTI_Handler(void);
void Task_LCD(void* pvParameters);
void Task_Button(void* pvParameters);


/* ISR Callback */
void APP_EXTI_Handler(void)
{
    buttonPressedFlag = 1; // Set flag to indicate button press
}

int main(void)
{
	/* Initialize hardware */
	HLCD_vInit();
	MEXTI_vInit();
	MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
	MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

	/* Counting semaphore and initially take it */
	xSemaphore = xSemaphoreCreateCounting(5, 0);

	/* Create tasks */
	xTaskCreate(Task_LCD, (signed const char*)"LCD", 200, NULL, 1, NULL);
	xTaskCreate(Task_Button, (signed const char*)"Button", 200, NULL, 2, NULL);

	 /* Register ISR callback */
	MEXTI_vCallBackFunction(APP_EXTI_Handler,0);

	/* Start scheduler */
	vTaskStartScheduler();

	while(1); // Should never reach here
	return 0;
}

/* Task 1: Monitors button flag and gives semaphore */
void Task_Button(void* pvParameters)
{
    while(1)
    {
        if(buttonPressedFlag)
        {
            buttonPressedFlag = 0; // Clear flag
            xSemaphoreGive(xSemaphore);
        }
        vTaskDelay(10);
    }
}

/* Task 2: Waits for semaphore and writes to LCD */
void Task_LCD(void* pvParameters)
{

	while(1)
	{
		HLCD_vClearScreen();

		/* Waits for semaphore */
		if (xSemaphoreTake( xSemaphore, portMAX_DELAY ) == pdTRUE )
		{

			HLCD_vDisplayString((const s8*)"BTN pressed");
		}
		vTaskDelay(50);

	}
}
	
```

## Lab 4:
We have two tasks that communicate with each other
using a Message queue:
1. `First task:` Check the keypad every 50ms and send the number of the pressed button in the queue.
2. `Second task:` Receive the key number from the queue and display it on the LCD.

```c
/*
 * main.c
 *
 *  Created on: Aug 7, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 8000000UL
#include <util/delay.h>

#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/KPD/KPD_int.h"

#include "../FreeRTOS/FreeRTOS.h"
#include "../FreeRTOS/task.h"
#include "../FreeRTOS/queue.h"

/* Define queue handle */
xQueueHandle KeyQueue;

u8 KeyMap[KPD_ROWS][KPD_COLS] =
{
	    {'1', '2', '3', 'A'},
	    {'4', '5', '6', 'B'},
	    {'7', '8', '9', 'C'},
	    {'*', '0', '#', 'D'}
};

/* Function Prototypes */
void Task_Keypad(void* pvParameters);
void Task_LCD(void* pvParameters);

int main(void)
{
	/* Initialize hardware */
	HLCD_vInit();
	HKPD_vInit();

	/* Create queue (length = 5, each item = 1 byte) */
	KeyQueue = xQueueCreate(5, sizeof(u8));


	/* Create tasks */
	xTaskCreate(Task_Keypad, "Keypad", 200, NULL, 2, NULL);
	xTaskCreate(Task_LCD, "LCD", 200, NULL, 1, NULL);

	/* Start scheduler */
	vTaskStartScheduler();

	while(1); // Should never reach here
	return 0;
}

/* Task to check keypad every 50ms and send key to queue */
void Task_Keypad(void* pvParameters)
{
	u8 key;
	while(1)
	{
		key = HKPD_u8GetPressedKey(KeyMap);
		if (key != NO_KEY) // Assume 0xFF = No key pressed
		{
			xQueueSend(KeyQueue, &key, 0); // Send without waiting
		}
		vTaskDelay(50); // 50ms polling rate
	}
}

/* Task to receive key from queue and display it */
void Task_LCD(void* pvParameters)
{
	u8 key;
	while(1)
	{
		if (xQueueReceive(KeyQueue, &key, portMAX_DELAY) == pdTRUE)
		{
			HLCD_vClearScreen();
			HLCD_vSendChar(key);
		}
	}
}
```