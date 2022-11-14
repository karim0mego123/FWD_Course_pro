/*
 * Interrupt.h
 *
 * Created: 11/11/2022 10:48:43 PM
 *  Author: karim
 */ 


#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "..\DIO_Driver\DIO.h"

#define EXT_INT_0 __vector_1
// External interrupt request 1
#define EXT_INT_1 __vector_2
// External interrupt request 2
#define EXT_INT_2 __vector_3

// Set global interrupts, set the I-bit in status register to 1
#define  sei() __asm__ __volatile__ ("sei" ::: "memory")

// Clear Global interrupts, set the I-bit in status register to 0
#define cli() __asm__ __volatile__ ("cli" ::: "memory")

// ISR defition
#define ISR(INT_VECT)void INT_VECT(void) __attribute__ ((signal, used));\
void INT_VECT(void)

void interrupt_rising_init(void);

#endif /* INTERRUPT_H_ */