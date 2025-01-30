/*
 * SERVO_Program.c
 *
 *  Created on: Sep 11, 2023
 *      Author: Hegazy
 */
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/Timer1/Timer1_Interface.h"
#include "../../MCAL/DIO/DIO_Interface.h"

#include "SERVO_Interface.h"
#include "SERVO_Config.h"
#include "SERVO_Private.h"



void SERVO_voidInit(void)
{
	TIMER1_voidInit();
	DIO_voidSetPinDirection(SERVO_PORT,SERVO_PIN,OUTPUT);


}

void SERVO_voidRotate(u8 Copy_u8Angle)
{
	TIMER1_voidSetTopValue(20000);
	TIMER1_voidFastPWMNonIntvered(TIMER_CHANNELA ,PRESCALAR_8_CLOCK);

	u16 Local_u8Angle =((u16)(Copy_u8Angle*10))+750 ;
	TIMER1_voidSetDutyCycle(TIMER_CHANNELA ,Local_u8Angle);

}
