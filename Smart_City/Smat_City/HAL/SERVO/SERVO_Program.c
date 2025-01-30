/************************************/
/* File      : SERVO_Program.c      */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V1.0                 */
/************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "../../MCAL/DIO/DIO_Interface.h"
#include "../../MCAL/TIMER/TIMER_Interface.h"
#include "SERVO_Interface.h"
#include "SERVO_Config.h"
#include "SERVO_Private.h"



void SERVO_voidInit(void)
{
	TMR0_voidInit();
	TIMER1_voidInit();
	TMR2_voidInit();
	DIO_voidSetPinDirection(SERVO_PORT,SERVO_PIN1,OUTPUT); //Timer 1 Channel A
	DIO_voidSetPinDirection(SERVO_PORT,SERVO_PIN2,OUTPUT); //Timer 1 Channel B
	DIO_voidSetPinDirection(PORTD,PIN7,OUTPUT);
	DIO_voidSetPinDirection(PORTB,PIN3,OUTPUT);
}
void SERVO_voidRotate1(u8 Copy_u8Angle)
{
	TIMER1_voidSetTopValue(20000);
	TIMER1_voidFastPWMNonIntvered(TIMER_CHANNELA ,PRESCALAR_8_CLOCK);

	u16 Local_u8Angle =((u16)(Copy_u8Angle*10))+750 ;
	TIMER1_voidSetDutyCycle(TIMER_CHANNELA ,Local_u8Angle);

}
void SERVO_voidRotate2(u8 Copy_u8Angle)
{
	TIMER1_voidSetTopValue(20000);
	TIMER1_voidFastPWMNonIntvered(TIMER_CHANNELB ,PRESCALAR_8_CLOCK);

	u16 Local_u8Angle =((u16)(Copy_u8Angle*10))+750 ;
	TIMER1_voidSetDutyCycle(TIMER_CHANNELB ,Local_u8Angle);

}
void SERVO_voidRotate3(u8 Copy_u8Angle)
{
	    // Configure Timer0 for Fast PWM, non-inverted mode with prescaler 64
	    TMR0_voidFastPWMNonInverted(PRESCALAR_64_CLOCK);

	    // Convert angle to duty cycle (50-250 corresponds to 1ms-2ms pulse width for 0-180 degrees)
	    u16 Local_u8Angle = ((u16)(Copy_u8Angle * 2)) + 500;

	    // Set the calculated duty cycle
	    TMR0_voidSetDutyCycle(Local_u8Angle);
}
void SERVO_voidRotate4(u8 Copy_u8Angle)
{
	    // Configure Timer0 for Fast PWM, non-inverted mode with prescaler 64
	    TMR2_voidFastPWMNonInverted(PRESCALAR_64_CLOCK);

	    // Calculate duty cycle based on angle (0° to 180°)
	    u16 Local_u8Angle = (u16)(750 + (9.722 * Copy_u8Angle));

	    // Set the calculated duty cycle
	    TMR2_voidSetDutyCycle(Local_u8Angle);
}
