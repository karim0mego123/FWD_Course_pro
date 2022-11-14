/*
 * Interrupt.c
 *
 * Created: 11/11/2022 10:49:00 PM
 *  Author: karim
 */ 
#include "Interrupt.h"

void interrupt_rising_init(void)
{
	
	// 1. Enable global interrupt(setting bit 7 in status register to 1
	sei();
	// 2. Choosing the external interrupt  (sense on the rising edge)
	MCUCR |= (1 << 0) | (1 << 1);
	// 3.Enable External interrupt 0(INT0)
	GICR |= (1 << 6);
	
}