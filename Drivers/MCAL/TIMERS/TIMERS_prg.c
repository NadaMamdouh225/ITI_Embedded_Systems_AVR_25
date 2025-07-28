/*
 * TIMERS_prg.c
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "TIMERS_int.h"
#include "TIMERS_prv.h"

void MTIMERS_vInit(void)
{
	/* Waveform generation (normal OF mode)*/
	/* Stop timer */
	TCCR0 = 0x00;

	/*Enable interrupt OF mode */
	SET_BIT(TIMSK,0);

}
void MTIMERS_vSetIntervalAsych_CB(void (*Fptr)(void), u32 A_u32Interval)
{

}
void MTIMERS_vStartTimer(void)
{
#if	TIMERID_0 == ENABLE
	TCCR0 = (TCCR0 & 0xF8) | (0x07 & CLK_SELECT_PRESCALER);

#endif


}
void MTIMERS_vStopTimer(void)
{
#if	TIMERID_0 == ENABLE
	CLR_BIT(TCCR0, 0);
	CLR_BIT(TCCR0, 1);
	CLR_BIT(TCCR0, 2);

#endif

}




void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{

}
