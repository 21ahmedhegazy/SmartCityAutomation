/*
 * Motor_Program.c
 *
 *  Created on: Aug 26, 2023
 *      Author: Hegazy
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "Motor_Interface.h"
#include "Motor_Config.h"
#include "util/delay.h"


void DCMotor_voidInitPB(void)
{
DIO_voidSetPinDirection(DC_Motor_Port,DC_Motor_Pin1,OUTPUT);
DIO_voidSetPinDirection(DC_Motor_Port,DC_Motor_Pin2,OUTPUT);
}

void DCMotor_voidInit(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
	DIO_voidSetPinDirection(Copy_u8PortID,Copy_u8PinID,OUTPUT);
}

void DCMotor_voidMotorON(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{
	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8PinID,HIGH);
}

void DCMotor_voidMotorOFF(u8 Copy_u8PortID ,u8 Copy_u8PinID)
{

	DIO_voidSetPinValue(Copy_u8PortID,Copy_u8PinID,LOW);
}
void DCMotor_voidRotateCW(void)
{
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin1,LOW);
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin2,HIGH);
}

void DCMotor_voidRotateACW(void)
{
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin2,LOW);
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin1,HIGH);
}

void DCMotor_voidStopMotor(void)
{
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin1,LOW);
	DIO_voidSetPinValue(DC_Motor_Port,DC_Motor_Pin2,LOW);
}
