/*
 * BUTTON.h
 *
 * Created: 11/13/2022 11:26:54 PM
 *  Author: karim
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "..\LED_Driver\LED.h"
#include "..\..\MCAL\Timer_Driver\Timer.h"

// define button1 port and pin
#define EXT_INT_BUTTON_PORT PORT_D
#define EXT_INT_BUTTON_PIN PIN2

//functions prototypes

//initialization
void Button_init(uint8_t buttonPort, uint8_t buttonPin);

// get button status
void Button_get_state(uint8_t buttonPort, uint8_t buttonPin, uint8_t *value);

#endif /* BUTTON_H_ */