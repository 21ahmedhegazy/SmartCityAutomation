/*
 * BUZZER_Program.c
 *
 *  Created on: Sep 26, 2023
 *      Author: Hegazy
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "BUZZER_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"


void BUZZER_voidInit(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
	DIO_voidSetPinDirection(Copy_u8PortID ,Copy_u8PinID ,OUTPUT);
}

void BUZZER_voidBuzzerON(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
 DIO_voidSetPinValue(Copy_u8PortID ,Copy_u8PinID ,HIGH);
}

void BUZZER_voidBuzzerOFF(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
	 DIO_voidSetPinValue(Copy_u8PortID ,Copy_u8PinID ,LOW);
}

void BUZZER_voidBuzzerToggel(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
	DIO_voidTogglePinValue(Copy_u8PortID ,Copy_u8PinID);
}
