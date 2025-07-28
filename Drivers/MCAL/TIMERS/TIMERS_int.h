/*
 * TIMERS_int.h
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */

#ifndef MCAL_TIMERS_TIMERS_INT_H_
#define MCAL_TIMERS_TIMERS_INT_H_

#define ENABLE	1
#define DISABLE	0

#define TIMERID_0  	ENABLE
#define TIMERID_1  	DISABLE
#define TIMERID_2  	DISABLE


#define NO_CLK				0x00
#define CLK_NO_PRESCALLING	0x01
#define CLK_8				0x02


#define CLK_SELECT_PRESCALER	CLK_8



void MTIMERS_vInit(void);
void MTIMERS_vSetIntervalAsych_CB(void (*Fptr)(void), u32 A_u32T_required);

// CTC
void MTIMERS_vSetInterval_CTC(void (*Fptr)(void),u32 A_u32T_required, u8 A_u8OCR_val);

void MTIMERS_vStartTimer(void);
void MTIMERS_vStopTimer(void);

#endif /* MCAL_TIMERS_TIMERS_INT_H_ */
