/*
 * Timer.c
 *
 * Created: 11/11/2022 10:47:34 PM
 *  Author: karim
 */ 

#include "Timer.h"

void TIMER_init(void)
{
	// 1. set timer mode to normal mode
	TCCR0_BASE = 0X00; // Normal mode
	// 2. Set timer initial value to 0
	TCNT0_BASE = 0x00;
}
void TIMER_start(uint16_t preScalar, uint32_t number_of_overflow)
{
	uint32_t overflowCounter = 0;
	switch (preScalar)
	{
		case 1:
		TCCR0_BASE |= (1 << 0); // set pin0
		break;
		case 8:
		TCCR0_BASE |= (1 << 1); // set pin1
		break;
		case 64:
		TCCR0_BASE |= 3; // set pin0 and pin1
		break;
		case 256:
		TCCR0_BASE |= (1 << 2); // set pin2
		break;
		case 1024:
		TCCR0_BASE |= 5; // set pin0 and pin2
		break;
		default:
		// Error handling
		break;
	}
	// Repeated number of overflow times
	while (overflowCounter < number_of_overflow)
	{
		// wait the overflow flat to be set
		while ((TIFR_BASE & (1 << 0)) == 0);
		// Clear the overflow flag
		TIFR_BASE |= (1 << 0);
		overflowCounter++;
	}
}
void TIMER_stop(void)
{
	// Timer stop
	TCCR0_BASE = 0x00;
}

void delay_5s(void)
{
	TIMER_start(256, 77);
	TIMER_stop();
}