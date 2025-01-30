/*********************************************************/
/* Component : STEPPER_MOTOR                                     */
/* File      : STM_program.c                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/Bit_Maths.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "STEPERR_interface.h"
#include "STEPERR_config.h"
#include <util/delay.h>

void STEPPER_voidInit(void)
{
    // Initialize the stepper motor pins as output
    DIO_voidSetPinDirection(STEPPER_PORT, Coil_Blue, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(STEPPER_PORT, Coil_Pink, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(STEPPER_PORT, Coil_Yellow, DIO_PIN_OUTPUT);
    DIO_voidSetPinDirection(STEPPER_PORT, Coil_Orange, DIO_PIN_OUTPUT);

    // Set all the pins to high initially
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
}

void Stepper_voidRotateCW(void)
{
    // Rotate stepper motor clockwise
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_LOW_OUTPUT);
    _delay_ms(2);
}

void Stepper_voidRotateACW(void)
{
    // Rotate stepper motor anticlockwise
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_LOW_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);
}

void Stepper_voidHalfSetpRotateCW(void)
{
    // Half step clockwise rotation logic
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_LOW_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    DIO_voidSetPinValue(STEPPER_PORT, Coil_Blue, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Pink, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Yellow, DIO_HIGH_OUTPUT);
    DIO_voidSetPinValue(STEPPER_PORT, Coil_Orange, DIO_HIGH_OUTPUT);
    _delay_ms(2);

    // (Continue with the remaining half-step sequence)
}

void Stepper_voidHalfSetpRotateACW(void)
{
    // Half step anticlockwise rotation logic (same as CW, but reverse pin states)
}
