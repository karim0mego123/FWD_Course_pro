/*
 * Registers.h
 *
 * Created: 11/11/2022 10:39:07 PM
 *  Author: karim
 */ 


#ifndef REGISTERS_H_
#define REGISTERS_H_


#include "Types.h"
#include "Utils.h"

/************************************************************************/
/*						MCU_Regester                                    */
/************************************************************************/

/************************************************************************/
/*							DIO_Regesters                               */
/************************************************************************/
// All pin configuration
#define PIN0	0
#define PIN1	1
#define PIN2	2
#define PIN3	3
#define PIN4	4
#define PIN5	5
#define PIN6	6
#define PIN7	7

// PORTA

#define PORTA_BASE	*(volatile uint8_t *)(0x3B)
#define DDRA_BASE	*(volatile uint8_t *)(0x3A)
#define PINA_BASE	*(volatile uint8_t *)(0x39)

// PORTB
#define PORTB_BASE	*(volatile uint8_t *)(0x38)
#define DDRB_BASE	*(volatile uint8_t *)(0x37)
#define PINB_BASE	*(volatile uint8_t *)(0x36)

// PORTC
#define PORTC_BASE	*(volatile uint8_t *)(0x35)
#define DDRC_BASE	*(volatile uint8_t *)(0x34)
#define PINC_BASE	*(volatile uint8_t *)(0x33)

// PORTD
#define PORTD_BASE	*(volatile uint8_t *)(0x32)
#define DDRD_BASE	*(volatile uint8_t *)(0x31)
#define PIND_BASE	*(volatile uint8_t *)(0x30)

/************************************************************************/
/*							Timer_Regesters                             */
/************************************************************************/
/* Timer 0*/
// Diraction_Defination
#define IN	0
#define OUT	1

// Value_Defination
#define High	1
#define Low		0

#define TCCR0_BASE	*(volatile uint8_t *)(0x53)
#define CS00	0
#define	CS01	1
#define	CS02	2
#define WGM01	3
#define COM00	4
#define COM01	5
#define WGM00	6
#define FOC0	7

#define TCNT0_BASE	*(volatile uint8_t *)(0x52)
#define OCR0_BASE	*(volatile uint8_t *)(0x5C)

#define TIMSK_BASE	*(volatile uint8_t *)(0x59)
#define TOIE0	0
#define OCIE0	1
#define TOIE1	2
#define OCIE1B	3
#define OCIE1A	4
#define TICIE1	5
#define TOIE2	6
#define OCIE2	7

#define TIFR_BASE	*(volatile uint8_t *)(0x58)
#define TOV0	0
#define	OCF0	1
#define	TOV1	2
#define	OCF1B	3
#define	OCF1A	4
#define ICF1	5
#define	TOV2	6
#define	OCF2	7

// INTERRUPT
#define	MCUCR	*(volatile uint8_t *)(0x55)
#define ISC00	0
#define ISC01	1
#define ISC10	2
#define ISC11	3


#define	MCUCSR	*(volatile uint8_t *)(0x54)
#define ISC2	6

#define	GICR	*(volatile uint8_t *)(0x5B)
#define INT1	7
#define INT0	6
#define INT2	5

#define	GIFR	*(volatile uint8_t *)(0x5A)
#define INTF1	7
#define INTF0	6
#define INTF2	5

#define	SREG	*(volatile uint8_t *)(0x5F)



#define INT0_vect		__vector_1
#define INT1_vect		__vector_2
#define INT2_vect		__vector_3

#define TIMSK   *(volatile uint8_t *)(0x39)
#define TOIE0   0
#define OCIE0   1
#define TOIE2   6
#define OCIE2   7
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5

//** LED port names **//
#define CAR_light 'A'
#define pedestrians_light 'B'

//** LED pin names **//
#define LED_green	0
#define LED_yellow	1
#define LED_red		2

#define phase_1 0
#define phase_2 1
#define phase_3 2
#define phase_4 3

#define Button_1_Portd	PORT_D
#define Button_1_PIN2	PIN0


#endif /* REGISTERS_H_ */