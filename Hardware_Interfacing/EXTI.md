# Session: EXTI

## Lab 1: Interfacing with INT0 without Callback mechanism

<img src="../assets/exti.png">

<br>

```c
/*
 * main.c
 *
 *  Created on: Jul 22, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include <util/delay.h>

#include <avr/io.h>
#include <avr/interrupt.h>

// hw interrupt isr
ISR(INT0_vect)
{
	// my function
	MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}


int main()
{
	// interrupt pin
	MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
	// activate pull up resistor
	MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

	// led pin
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	MEXTI_vInit();
	MGIE_vEnableGlobalInterrupt();

	while(1)
	{

	}

	return 0;
}

```

## Lab 2: Using Callback mechanism
```c
/*
 * main.c
 *
 *  Created on: Jul 22, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/EXTI/EXTI_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include <util/delay.h>

void Toggel_func(void)
{
	MDIO_vTogPinVal(DIO_PORTA, DIO_PIN0);
}

int main()
{
	// configure led as output
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

	// configure switch as input and activate pull up resistor
	MDIO_vSetPinDir(DIO_PORTD, DIO_PIN2, DIO_INPUT);
	MDIO_vSetPinVal(DIO_PORTD, DIO_PIN2, DIO_HIGH);

	MEXTI_vInit();
	MGIE_vEnableGlobalInterrupt();

	// using callback mechanism to pass a function to EXTI_prg.c and 0 means using INT0
	MEXTI_vCallBackFunction(Toggel_func, 0);

	while(1)
	{


	}

	return 0;
}

```
