/*
 * TIMERS_prv.h
 *
 *  Created on: Jul 27, 2025
 *      Author: Nada Mamdouh
 */

#ifndef MCAL_TIMERS_TIMERS_PRV_H_
#define MCAL_TIMERS_TIMERS_PRV_H_

/* --------- Timer 0 --------- */
#define TCCR0	*((volatile u8*)(0x53))
#define TCNT0	*((volatile u8*)(0x52))
#define OCR0	*((volatile u8*)(0x5C))
#define TIMSK	*((volatile u8*)(0x59))
#define TIFR	*((volatile u8*)(0x58))

/* --------- Timer 1 --------- */
#define TCCR1A	*((volatile u8*)(0x4F))
#define TCCR1B	*((volatile u8*)(0x4E))
#define TCNT1	*((volatile u16*)(0x4C))
#define OCR1A	*((volatile u16*)(0x4A))
#define OCR1B	*((volatile u16*)(0x48))
#define ICR1	*((volatile u16*)(0x46))



#endif /* MCAL_TIMERS_TIMERS_PRV_H_ */
