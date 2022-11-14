/*
 * LED.h
 *
 * Created: 11/11/2022 10:45:25 PM
 *  Author: karim
 */ 


#ifndef _DIO_H_
#define _DIO_H_

#include "..\..\Utilities\Types.h"
#include "..\..\Utilities\Utils.h"
#include "..\..\Utilities\Registers.h"




// All Driver Macros
#define PORT_A	'A'
#define PORT_B	'B'
#define PORT_C	'C'
#define PORT_D	'D'

// DIO_PrortoTypes
void DIO_Init( uint8_t PortNumber , uint8_t PinNumber , uint8_t Direction ) ;
void DIO_Write( uint8_t PortNumber , uint8_t PinNumber , uint8_t value  ) ;
void DIO_Read( uint8_t PortNumber , uint8_t PinNumber , uint8_t* value  );
void DIO_Toggle( uint8_t PortNumber , uint8_t PinNumber  );


//** PORT states **//
#define LOW 0
#define HIGH 1


//** PORT directions **//
#define IN 0
#define OUT 1


#endif /* LED_H_ */