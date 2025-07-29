# Session: Servo

## Lab 1: Servo
```c
/*
 * main.c
 *
 *  Created on: Jul 28, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/TIMERS/TIMERS_int.h"
#include <util/delay.h>



int main()
{
	MDIO_vSetPinDir(DIO_PORTD, DIO_PIN5, DIO_OUTPUT);

	MTIMERS_vInit();
	u8 angle = 0;
	MTIMERS_vSetCompareMatch(TIM_1_A,((125*angle)/180)+125);
	_delay_ms(300);

	angle = 90;
	MTIMERS_vSetCompareMatch(TIM_1_A,((125*angle)/180)+125);
	_delay_ms(300);

	angle = 180;
	MTIMERS_vSetCompareMatch(TIM_1_A,((125*angle)/180)+125);
	_delay_ms(300);

	while(1)
	{


	}

	return 0;
}
```