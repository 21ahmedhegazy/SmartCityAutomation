/*
 * STEPPER_Program.c
 *
 *  Created on: Aug 23, 2023
 *      Author: Hegazy
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "STEPPER_Interface.h"
#include "STEPPER_Config.h"
#include <util/delay.h>

void STEPPER_voidInit(void)
{
	//SET PINS OF STEPPER OUTPUT
	DIO_voidSetPinDirection(STEPPER_PORT,Coil_Blue,OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT,Coil_Pink,OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT,Coil_Yellow,OUTPUT);
	DIO_voidSetPinDirection(STEPPER_PORT,Coil_Orange,OUTPUT);

	//SET PINS OF STEPPER HIGH
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);

}

void Stepper_voidRotateCW(void)
{
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
}

void Stepper_voidRotateACW(void)
{
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
}

void Stepper_voidHalfSetpRotateCW(void)
{
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
}

void Stepper_voidHalfSetpRotateACW(void)
{
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,LOW);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Blue,LOW);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Pink,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Yellow,HIGH);
	DIO_voidSetPinValue(STEPPER_PORT,Coil_Orange,HIGH);
	_delay_ms(2);






}
