# Session : DIO
## Lab 1: Write a C code to turn on LED on Pin A0
```c
/*
 * main.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0b00000001;
	PORTA = 0b00000001;
	while(1)
	{


	}

	return 0;
}

```
## Lab 2: Write a C code to turn on LED on Pin A0 for 1 second and then turn it off
```c
/*
 * main.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0b00000001;
	PORTA = 0b00000001;
	_delay_ms(1000);
	while(1)
	{


	}

	return 0;
}

```

## Lab 3: Write a C code to blink a LED Every 1 second

```c
/*
 * main.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main()
{
	DDRA = 0b00000001;

	while(1)
	{
		PORTA = 0b00000001;
		_delay_ms(1000);
		PORTA = 0b00000001;
		_delay_ms(1000);
	}

	return 0;
}

```
## Lab 4: Write a C Code that apply Some LED animations

```c
/*
 * main.c
 *
 *  Created on: Jul 15, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"

int main()
{
	DDRA = 0b00001111;
	PORTA = 0b00000000;

	while(1)
	{
		for(u8 index = 0; index <4; index++)
		{
			SET_BIT(PORTA, index);
			_delay_ms(1000);
		}
		for(u8 index = 4; index > 0; index--)
		{
			CLR_BIT(PORTA, (index-1));
			_delay_ms(1000);
		}

	}

	return 0;
}

```
## Lab 5: Write a C code to turn on LED on Pin A0 using DIO driver

```c
/*
 * main.c
 *
 *  Created on: Jul 16, 2025
 *      Author: Nada Mamdouh
 */

#define F_CPU 	8000000UL
//#include <avr/io.h>
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include <util/delay.h>

int main()
{
	/* Configuration / Initialization */

	// Pin Direction
	DIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);

	// Pin A0 Outputs 5v
	DIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);

	while(1)
	{

	}
	return 0 ;
}
```