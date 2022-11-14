/*
 * LED.c
 *
 * Created: 11/13/2022 11:26:29 PM
 *  Author: karim
 */ 

#include "LED.h"

void LED_Init ( uint8_t LedPort , uint8_t LedPin )
{
	DIO_Init(LedPort,LedPin,OUT) ;
}
void LED_ON ( uint8_t LedPort , uint8_t LedPin )
{
	DIO_Write(LedPort,LedPin,High) ;
}
void LED_OFF ( uint8_t LedPort , uint8_t LedPin )
{
	DIO_Write(LedPort,LedPin,Low) ;
}
void LED_TOGGLE ( uint8_t LedPort , uint8_t LedPin )
{
	DIO_Toggle(LedPort,LedPin) ;
}