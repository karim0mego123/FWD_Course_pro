/*
 * Timer.h
 *
 * Created: 11/11/2022 10:47:47 PM
 *  Author: karim
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#include "..\..\Utilities\Registers.h"
#include "..\Interrupt_Driver\Interrupt.h"


void TIMER_init(void);
void TIMER_start(uint16_t preScalar, uint32_t number_of_overflow);
void TIMER_stop(void);
void delay_5s(void);

#endif /* TIMER_H_ */