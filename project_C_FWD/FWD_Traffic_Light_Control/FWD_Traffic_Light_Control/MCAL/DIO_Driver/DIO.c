/*
 * LED.c
 *
 * Created: 11/11/2022 10:45:35 PM
 *  Author: karim
 */ 
#include "DIO.h"

void DIO_Init( uint8_t PortNumber , uint8_t PinNumber , uint8_t Direction )
{
	switch( PortNumber )
	{
		case PORT_A :
		if ( Direction == OUT )
		{
			DDRA_BASE |= (1<<PinNumber) ;
		}
		else if ( Direction == IN )
		{
			DDRA_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_B :
		if ( Direction == OUT )
		{
			DDRB_BASE |= (1<<PinNumber) ;
		}
		else if ( Direction == IN )
		{
			DDRB_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_C :
		if ( Direction == OUT )
		{
			DDRC_BASE |= (1<<PinNumber) ;
		}
		else if ( Direction == IN )
		{
			DDRC_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_D :
		if ( Direction == OUT )
		{
			DDRD_BASE |= (1<<PinNumber) ;
		}
		else if ( Direction == IN )
		{
			DDRD_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
	}
}
void DIO_Write( uint8_t PortNumber , uint8_t PinNumber , uint8_t value  )
{
	switch( PortNumber )
	{
		case PORT_A :
		if ( value == High )
		{
			PORTA_BASE |= (1<<PinNumber) ;
		}
		else if ( value == Low )
		{
			PORTA_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_B :
		if ( value == High )
		{
			PORTB_BASE |= (1<<PinNumber) ;
		}
		else if ( value == Low )
		{
			PORTB_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_C :
		if ( value == High )
		{
			PORTC_BASE |= (1<<PinNumber) ;
		}
		else if ( value == Low )
		{
			PORTC_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
		case PORT_D :
		if ( value == High )
		{
			PORTD_BASE |= (1<<PinNumber) ;
		}
		else if ( value == Low )
		{
			PORTD_BASE &= ~(1<<PinNumber) ;
		}
		else
		{
			//	Error Handling
		}
		break ;
	}
}
void DIO_Read( uint8_t PortNumber , uint8_t PinNumber , uint8_t* value  )
{
	switch(PortNumber)
	{
		case PORT_A :
		*(value) = (PINA_BASE &(1<<PinNumber))>>PinNumber ;
		break ;
		case PORT_B :
		*(value) = (PINB_BASE &(1<<PinNumber))>>PinNumber ;
		break;
		case PORT_C :
		*(value) = (PINC_BASE &(1<<PinNumber))>>PinNumber ;
		break;
		case PORT_D :
		*(value) = (PIND_BASE &(1<<PinNumber))>>PinNumber ;
		break;
		
	}
}
void DIO_Toggle( uint8_t PortNumber , uint8_t PinNumber  )
{
	switch(PortNumber)
	{
		case PORT_A :
		PORTA_BASE ^= (1<<PinNumber);
		break ;
		case PORT_B :
		PORTB_BASE ^= (1<<PinNumber);
		break ;
		case PORT_C :
		PORTC_BASE ^= (1<<PinNumber);
		break ;
		case PORT_D :
		PORTD_BASE ^= (1<<PinNumber);
		break ;
	}
}