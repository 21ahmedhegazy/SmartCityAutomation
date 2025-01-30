/*
 * main.c
 *
 *  Created on: Dec 6, 2024
 *      Author: Hegazy
 *      V.01
 */

#include <stdio.h>
#include <util/delay.h>




#include "LIB/Bit_Maths.h"
#include "LIB/STD_TYPES.h"

#include "MCAL/DIO/DIO_interface.h"
#include "MCAL/ADC/ADC_interface.h"
#include "MCAL/EXTI/EXTI_interface.h"
#include "MCAL/TIMER/TIMER_interface.h"
#include "MCAL/USART/USART_interface.h"
#include "MCAL/WDT/WDT_interface.h"
#include "HAL/BUZZER/BUZZER_interface.h"
#include "HAL/DC_MOTOR/DCM_interface.h"
#include "HAL/LED/LED_interface.h"
#include "HAL/SERVO/SERVO_interface.h"
#include "HAL/STEPER_MOTOR/STEPERR_interface.h"


void main(void)
{
	SERVO_Int();
	//LED_voidLedIni(DIO_PORTD,DIO_PIN3);
	LED_voidLedIni(DIO_PORTD,DIO_PIN3);





	while(1)
	{
		//LED_voidSetToggleLed(DIO_PORTD,DIO_PIN3);

		DOOR_voidDoorOpen();
		LED_voidSetLedOn(DIO_PORTD,DIO_PIN3);

		DOOR_voidDoorClose();
		LED_voidSetLedOff(DIO_PORTD,DIO_PIN3);

	}
}






