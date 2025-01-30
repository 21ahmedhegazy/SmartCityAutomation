/*********************************************************/
/* Component : SERVO                                     */
/* File      : SERVO_program.c                           */
/* Author    : Ahmed Hegazy                              */
/* Date      : 11 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/TIMER/TIMER_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/TIMER/TIMER_private.h"
#include "SERVO_config.h"
#include "SERVO_interface.h"
#include "SERVO_private.h"
#include <util/delay.h>

void SERVO_Int(void)
{
    // Set the selected channel to non-inverted fast PWM mode
	#if	CHANNEL == CHANNELB
        SET_BIT(TIMER1_TCCR1A, TCCRA_COM1B1);  // Non-inverted mode for Channel B
        CLR_BIT(TIMER1_TCCR1A, TCCRA_COM1B0);
	#elif CHANNEL == CHANNELA
        SET_BIT(TIMER1_TCCR1A, TCCRA_COM1A1);  // Non-inverted mode for Channel A
        CLR_BIT(TIMER1_TCCR1A, TCCRA_COM1A0);

    #else
        #error "Undefined channel selection"
    #endif

    // Set the output pin based on the config
    DIO_voidSetPinDirection(SERVO_PORT, SERVO_PIN, DIO_PIN_OUTPUT);  // Use the pin defined in the config file

    // Initialize Timer1
    TIMER1_voidInit();
}

void SERVO_Rotate(u8 Copy_u8Angle)
{
    // Set the timer top value for a 20ms period (50Hz PWM)
    TIMER1_voidSetTopValue(40000);

    u16 pulse_width_ticks = 2000 + ((u16)((Copy_u8Angle * 2000UL) / 180));

    // Set the prescaler for Timer1 (prescaler of 8 for better performance)
    #if CHANNEL == CHANNELA
        TIMER1_voidFastNonInvertedPWM(TIMER1_CHANNELA, TIMER1_PRESCALER_8);
        TIMER1_voidSetDutyCycle(TIMER1_CHANNELA, pulse_width_ticks);
    #elif CHANNEL == CHANNELB
        TIMER1_voidFastNonInvertedPWM(TIMER1_CHANNELB, TIMER1_PRESCALER_8);
        TIMER1_voidSetDutyCycle(TIMER1_CHANNELB, pulse_width_ticks);
    #else
        #error "Undefined channel selection"
    #endif
}


void DOOR_voidDoorOpen()
{
	SERVO_Rotate(180);
	_delay_ms(1000);
}

void DOOR_voidDoorClose()
{
	SERVO_Rotate(0);
	_delay_ms(1000);
}
