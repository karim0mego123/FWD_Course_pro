/*
 * App.c
 *
 * Created: 11/11/2022 10:36:45 PM
 *  Author: karim
 */ 
#include "App.h"
void App_init(void)
{
	// 1.  Set direction of LEDs to output
	// 1.1 cars' LEDs
	LED_Init(LED_C_RED_PORT, LED_C_RED_PIN);
	LED_Init(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_Init(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
	// 1.2 Pedestrians' LEDs
	LED_Init(LED_P_RED_PORT, LED_P_RED_PIN);
	LED_Init(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
	LED_Init(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
	// 2. Set direction of BUTTON  to input
	Button_init(EXT_INT_BUTTON_PORT, EXT_INT_BUTTON_PIN);
	// 3. initialize external interrupt 1
	interrupt_rising_init();
	// 4. initialize timer
	TIMER_init();
}
// To store the mode
EN_mode_t mode = NORMAL;
EN_button_color_t color;
EN_interrupt_state_t interrupt_state = INTERRUPT_OFF;
void App_start(void)
{
	while (1)
	{
		if (mode == NORMAL)
		{
			/*
				This is the normal mode in on demand traffic light control system, and there are the steps to implement this mode
				1. turn off all LEDs, to prevent the errors if it return from the pedestrian's mode
				2. turn on cars' Red LED and the pedestrian's Green LED
				2.1 check if the user push the button during this duration or not, to call the pedestrian's mode
				3. blink cars' Yellow LED and turn on the pedestrians' Red LED
				3.1 check if the user push the button during this duration or not, to call the pedestrian's mode
				4. Turn on cars' Green LED and blink the pedestrians' Yellow LED
			*/
			// 1. turn off all LEDs, to prevent the errors if it return from the pedestrian's mode
				
			TurnOffLEDs();
			// 2. turn on cars' Red LED and the pedestrian's Green LED
			LED_ON(LED_C_RED_PORT, LED_C_RED_PIN);
			LED_ON(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
			LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
			LED_OFF(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
			delay_5s();
			// 2.1 check if the user push the button during this duration or not, to call the pedestrian's mode
			if (interrupt_state == INTERRUPT_ON)
			{
				continue;
			}
			// 3. blink cars' Yellow LED and turn on the pedestrians' Red LED
			LED_OFF(LED_C_RED_PORT, LED_C_RED_PIN);
			LED_OFF(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
			LED_OFF(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
			LED_ON(LED_P_RED_PORT, LED_P_RED_PIN);
			toggle_LED_5s(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
			//3.1 check if the user push the button during this duration or not, to call the pedestrian's mode
			if (interrupt_state == INTERRUPT_ON)
			{
				continue;
			}
			//4. Turn on cars' Green LED and blink the pedestrians' Yellow LED
			LED_OFF(LED_P_RED_PORT, LED_P_RED_PIN);
			LED_OFF(LED_C_RED_PORT, LED_C_RED_PIN);
			LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
			LED_ON(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
			toggle_LED_5s(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
		}
		else if (mode == PEDESTRIAN)
		{
			PedestrianMode();
		}
	}
}
ISR(EXT_INT_0)
{
	/*
		Description:
		This represent the ISR for external interrupt 0
		1. check the color of cars' LED when the pedestrian push the button
		2. convert the mode from the normal to pedestrian mode
		3. turn on the interrupt state the indicate that the user can't implement the ISR again 
		until finish the first one
	*/ 
		// 1. check the color of cars' LED when the pedestrian push the button
	if (interrupt_state == INTERRUPT_OFF)
	{
		uint8_t value;
		DIO_Read(LED_C_RED_PORT, LED_C_RED_PIN, &value);
		if (value)
		{
			color = RED;
		}
		else
		{
			DIO_Read(LED_C_GREEN_PORT, LED_C_GREEN_PIN, &value);
			if (value)
			{

				color = GREEN;
			}
			else
			{
				color = YELLOW;
			}
		}
		//	2. convert the mode from the normal to pedestrian mode
		mode = PEDESTRIAN;
		// 3. turn on the interrupt state the indicate that the user can't implement the ISR again
		interrupt_state = INTERRUPT_ON;
	}
}

void PedestrianMode(void)
{
	/*
	Description:
	This function implement the pedestrian's mode
	1. turn off all LEDs, to prevent the errors if it return from the pedestrian's mode
	2. check the color of cars' LED when the pedestrian push the button
	3. implement the mode according to the cars' LED color
	4. continue the pedestrian mode until led cars pass 
		4.1 turn off cars' Red LED
		4.2 blink cars' Yellow LED and pedestrians' Yellow LED for 5 s
		4.3 Turn off Pedestrian's Yellow and Green LEDs and cars' Yellow LED
		4.4 Turn on cars' Red LED and the pedestrian's Green LED, to let cars pass 
	*/
	// 1. turn off all LEDs, to prevent the errors if it return from the pedestrian's mode
	TurnOffLEDs();
	// 	2. check the color of cars' LED when the pedestrian push the button
	// 3. implement the mode according to the cars' LED color
	
	if (color == RED)
	{
		RedLED();
	}
	else if (color == GREEN)
	{
		GreenLED();
	}
	else if (color == YELLOW)
	{
		YellowLED();
	}
	// 4. continue the pedestrian mode until led cars pass
	// 	4.1 turn off cars' Red LED
	LED_OFF(LED_C_RED_PORT, LED_C_RED_PIN);
	// 	4.2 blink cars' Yellow LED and pedestrians' Yellow LED for 5 s
	toggle_2_LEDs_5s(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN, LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	//	4.3 Turn off Pedestrian's Yellow and Green LEDs and cars' Yellow LED

	LED_OFF(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
	LED_OFF(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
	LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	// 		4.4 Turn on cars' Red LED and the pedestrian's Green LED, to let cars pass
	LED_ON(LED_P_RED_PORT, LED_P_RED_PIN);
	LED_ON(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
	delay_5s();
	interrupt_state = INTERRUPT_OFF;
	mode = NORMAL;
}
void TurnOffLEDs(void)
{
	/*
		Description:
		Turn off all the LEDs (for cars and pedestrians)
	*/
	// turn off all cars' LEDs
	LED_OFF(LED_C_RED_PORT, LED_C_RED_PIN);
	LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
	// turn off all pedestrian's LEDs
	LED_OFF(LED_P_RED_PORT, LED_P_RED_PIN);
	LED_OFF(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
	LED_OFF(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
}

void GreenLED(void)
{
	/*
	Description:
	1. turn on cars' Red LED and the pedestrian's Green LED
	2. then cars' Yellow LED and pedestrian's Yellow LED will be blink to tell the pedestrians 
	you should be ready to pass the road
	3. the cars' Red LED and the pedestrian's Green LED will be on( pedestrians will pass the road)
	*/
	LED_ON(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
	LED_ON(LED_P_RED_PORT, LED_P_RED_PIN);
	delay_5s();
	LED_OFF(LED_P_RED_PORT, LED_P_RED_PIN);
	toggle_2_LEDs_5s(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN, LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
	LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_C_GREEN_PORT, LED_C_GREEN_PIN);
	LED_ON(LED_C_RED_PORT, LED_C_RED_PIN);
	LED_ON(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
	delay_5s();
}
void RedLED(void)
{
	/*
		Description: 
		This function turn on cars' Red LED and Pedestrian's Green LED 
		To let pedestrians to pass the road
	*/
	LED_ON(LED_C_RED_PORT, LED_C_RED_PIN);
	LED_ON(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
	delay_5s();
}
void YellowLED(void)
{
	/*
	Description:
	1. turn on cars' Red LED and blink pedestrian's Yellow LED
	2. then cars' Yellow LED and  pedestrian's Yellow LED will be blink to tell the pedestrians 
	you should be ready to pass the road
	3. the cars' Red LED and the pedestrian's Green LED will be on( pedestrians will pass the road)
	*/
	LED_ON(LED_P_RED_PORT, LED_P_RED_PIN);
	toggle_LED_5s(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_P_RED_PORT, LED_P_RED_PIN);
	toggle_2_LEDs_5s(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN, LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_OFF(LED_P_YELLOW_PORT, LED_P_YELLOW_PIN);
	LED_OFF(LED_C_YELLOW_PORT, LED_C_YELLOW_PIN);
	LED_ON(LED_C_RED_PORT, LED_C_RED_PIN);
	LED_ON(LED_P_GREEN_PORT, LED_P_GREEN_PIN);
	delay_5s();
}
void toggle_2_LEDs_5s(uint8_t ledPort1, uint8_t ledPin1, uint8_t ledPort2, uint8_t ledPin2)
{
	/*
		Description:
		make a delay for 5 seconds, and blink two LEDs during this duration
	*/
	uint32_t overflowCounter = 0;

	TCCR0_BASE |= (1 << 2); // set pin2, 256 pre-scalar
	// Repeated number of overflow times
	while (overflowCounter < 77)
	{
		// wait the overflow flat to be set
		while ((TIFR_BASE & (1 << 0)) == 0)
			;
		// Clear the overflow flag
		TIFR_BASE |= (1 << 0);
		if (overflowCounter % 6 == 0)
		{
			LED_TOGGLE(ledPort1, ledPin1);
			LED_TOGGLE(ledPort2, ledPin2);
		}
		overflowCounter++;
	}
}
void toggle_LED_5s(uint8_t ledPort, uint8_t ledPin)
{
	/*
		Description:
		make a delay for 5 seconds, and blink one LED during this duration
	*/
	uint32_t overflowCounter = 0;

	TCCR0_BASE |= (1 << 2); // set pin2, 256 pre-scalar
	// Repeated number of overflow times
	while (overflowCounter < 77)
	{
		// wait the overflow flat to be set
		while ((TIFR_BASE & (1 << 0)) == 0)
		;
		// Clear the overflow flag
		TIFR_BASE |= (1 << 0);
		if (overflowCounter % 6 == 0)
		{
			LED_TOGGLE(ledPort, ledPin);
		}
		overflowCounter++;
	}
} 