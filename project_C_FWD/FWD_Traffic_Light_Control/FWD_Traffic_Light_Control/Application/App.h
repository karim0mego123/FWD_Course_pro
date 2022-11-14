/*
 * App.h
 *
 * Created: 11/11/2022 10:36:56 PM
 *  Author: karim
 */ 


#ifndef APP_H_
#define APP_H_

#include "..\HAL\LED_Driver\LED.h"
#include "..\HAL\BUTTON_Driver\BUTTON.h"
#include "..\MCAL\Interrupt_Driver\Interrupt.h"
#include "..\MCAL\Timer_Driver\Timer.h"

// enum for traffic light colors
typedef enum EN_button_color_t
{
	RED, YELLOW, GREEN
}EN_button_color_t;
// enum for mode
typedef enum EN_mode_t
{
	NORMAL, PEDESTRIAN
}EN_mode_t;
typedef enum EN_interrupt_state_t
{
	INTERRUPT_ON, INTERRUPT_OFF
}EN_interrupt_state_t;
// Function prototypes


void App_init(void);
void App_start(void);
void GreenLED(void);
void RedLED(void);
void YellowLED(void);
void PedestrianMode(void);
void TurnOffLEDs(void);
void toggle_2_LEDs_5s(uint8_t ledPort1, uint8_t ledPin1, uint8_t ledPort2, uint8_t ledPin2);
void toggle_LED_5s(uint8_t ledPort, uint8_t ledPin);


#endif /* APP_H_ */