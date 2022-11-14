/*
 * LED.h
 *
 * Created: 11/13/2022 11:26:41 PM
 *  Author: karim
 */ 


#ifndef LED_H_
#define LED_H_

#include "..\..\MCAL\DIO_Driver\DIO.h"

/************************************************************************/
/*					3LEDs for cars										*/
/************************************************************************/
// define led1 port and pin
#define LED_C_RED_PORT PORT_A
#define LED_C_RED_PIN PIN0
// define led2 port and pin
#define LED_C_YELLOW_PORT PORT_A
#define LED_C_YELLOW_PIN PIN1
// define led3 port and pin
#define LED_C_GREEN_PORT PORT_A
#define LED_C_GREEN_PIN PIN2

/************************************************************************/
/*					3LEDs for pedestrians                               */
/************************************************************************/
// define led1 port and pin
#define LED_P_RED_PORT PORT_B
#define LED_P_RED_PIN PIN0
// define led2 port and pin
#define LED_P_YELLOW_PORT PORT_B
#define LED_P_YELLOW_PIN PIN1
// define led3 port and pin
#define LED_P_GREEN_PORT PORT_B
#define LED_P_GREEN_PIN PIN2

void LED_Init ( uint8_t LedPort , uint8_t LedPin ) ;
void LED_ON ( uint8_t LedPort , uint8_t LedPin )  ;
void LED_OFF ( uint8_t LedPort , uint8_t LedPin ) ;
void LED_TOGGLE ( uint8_t LedPort , uint8_t LedPin ) ;


#endif /* LED_H_ */