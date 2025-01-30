/*********************************************************/
/* Component : BUZZER                                      */
/* File      : BUZZER_program.c                            */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 12 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/





#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"

#include "BUZZER_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"

// Initialize the buzzer pin as an output pin
void BUZZER_voidInt(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Initialize the pin as output using DIO functions
    DIO_voidSetPinDirection(Copy_u8PortID, Copy_u8PinID, DIO_PIN_OUTPUT);
}

// Turn on the buzzer by setting the pin high
void BUZZER_voidTurnOn(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Set the pin value to high to turn on the buzzer
    DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_HIGH_OUTPUT);
}

// Turn off the buzzer by setting the pin low
void BUZZER_voidTurnOff(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Set the pin value to low to turn off the buzzer
    DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_LOW_OUTPUT);
}

// Toggle the buzzer state (on to off or off to on)
void BUZZER_voidToggle(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Toggle the pin value to change the state of the buzzer
    DIO_voidTogglePin(Copy_u8PortID, Copy_u8PinID);
}
