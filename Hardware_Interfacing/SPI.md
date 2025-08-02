# Session: SPI
## Lab 1
```c
/*
 * main.c
 *
 *  Created on: Jul 31, 2025
 *      Author: Nada Mamdouh
 */
#define F_CPU 	8000000UL
#include "../LIB/STD_TYPES.h"
#include "../MCAL/DIO/DIO_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../MCAL/SPI/SPI_int.h"
#include <util/delay.h>

int main()
{
	u8 c = 0;
	MDIO_vSetPinDir(DIO_PORTA, DIO_PIN0, DIO_OUTPUT);
	MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_LOW);


	MSPI_vInit();
	c = MSPI_vTransceive('R');
	if(c == 'R')
	{
		MDIO_vSetPinVal(DIO_PORTA, DIO_PIN0, DIO_HIGH);
	}

	while(1)
	{

	}

	return 0;
}

```