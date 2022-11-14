/*
 * BUTTON.c
 *
 * Created: 11/13/2022 11:27:08 PM
 *  Author: karim
 */ 

#include "BUTTON.h"

void Button_init(uint8_t buttonPort, uint8_t buttonPin) // Button is an input device
{
	DIO_Init(buttonPort, buttonPin, IN);
}

// get button status
void Button_get_state(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value)
{
	DIO_Read(buttonPort, buttonPin, value);
}