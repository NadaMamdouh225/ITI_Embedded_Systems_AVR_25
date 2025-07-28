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

static void (*G_TIMER_OVF_CB)(void) = NULL;
static void(*G_TIMER_CTC_CB)(void) = NULL;

static u32 G_u32T_required=0;

void MTIMERS_vInit(void)
{
	//	/* Waveform generation (normal OF mode)*/
	//	/* Stop timer */
	//	TCCR0 = 0x00;
	//
	//	/*Enable interrupt OF mode */
	//	SET_BIT(TIMSK,0);
	TCCR0 = 0b00001000;
	/*Enable interrupt CTC mode */
	SET_BIT(TIMSK,1);


}
void MTIMERS_vSetIntervalAsych_CB(void (*Fptr)(void), u32 A_u32T_required)
{
	G_u32T_required = A_u32T_required;
	G_TIMER_OVF_CB = Fptr;
	MTIMERS_vStartTimer();
}
void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32T_required, u8 A_u8OCR_val)
{
	G_TIMER_CTC_CB = Fptr;
	G_u32T_required = A_u32T_required;
	OCR0 = A_u8OCR_val;
	MTIMERS_vStartTimer();
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
	static u32 LS_u32T_OVF = 0;
	LS_u32T_OVF++;
	if(LS_u32T_OVF == G_u32T_required)
	{
		if(G_TIMER_OVF_CB != NULL)
		{
			G_TIMER_OVF_CB();
			LS_u32T_OVF = 0;
		}
	}

}

void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	static u32 LS_u32Counter = 0;
	LS_u32Counter++;
	if(LS_u32Counter == G_u32T_required)
	{
		if(G_TIMER_CTC_CB != NULL)
		{
			G_TIMER_CTC_CB();
			LS_u32Counter = 0;
		}
	}
}

