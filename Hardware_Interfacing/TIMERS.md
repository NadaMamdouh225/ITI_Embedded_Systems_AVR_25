# Session: Timers
## Lab 1: Overflow mode
```c
/*
 * main.c
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMERS/TIMERS_int.h"
#include <util/delay.h>

void Toggle(void)
{
	MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

int main()
{
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	MTIMERS_vInit();
	MGIE_vEnableGlobalInterrupt();
	// toggle each 500ms
	MTIMERS_vSetIntervalAsych_CB(Toggle,2000);


	while(1)
	{


	}




	return 0;
}

```
## Lab 2: CTC mode
```c
/*
 * main.c
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMERS/TIMERS_int.h"
#include <util/delay.h>

void Toggle(void)
{
	MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

int main()
{
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	MTIMERS_vInit();
	MGIE_vEnableGlobalInterrupt();
	// toggle each 500ms
	MTIMERS_vSetInterval_CTC_Asynch(2000, 250,Toggle);


	while(1)
	{


	}




	return 0;
}

```
## Lab 3: PWM fading LED in and out

```c
/*
 * main.c
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/ADC/ADC_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMERS/TIMERS_int.h"
#include <util/delay.h>


int main()
{
	MDIO_vSetPinDir(DIO_PORTB, DIO_PIN3, DIO_OUTPUT);
	MTIMERS_vInit();
	MTIMERS_vStartTimer();


	while(1)
	{
		//fade in
		for(u8 i=0;i<255;i++)
		{
			MTIMERS_vSetCompareValue(i);
			_delay_ms(20);
		}
		//fade out
		for(u8 i=255; i>0;i--)
		{
			MTIMERS_vSetCompareValue(i-1);
			_delay_ms(20);
		}

	}


	return 0;
}

```
