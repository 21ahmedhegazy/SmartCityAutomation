/************************************/
/* Component : LED                */
/* File      : LED_program.c     */
/* Author    :Ahmed Hegazy           */
/* Date 	 : 21/7/2023            */
/* Version 	 : V1.0                 */
/************************************/

#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"  // Include the DIO functions
#include "LED_interface.h"

// Initialize an LED pin as output
void LED_voidLedIni(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Set the pin as output
    DIO_voidSetPinDirection(Copy_u8PortID, Copy_u8PinID, DIO_PIN_OUTPUT);
}

// Initialize the entire port for LEDs (e.g., PORTB, PORTC, or PORTD)
void LED_voidLPortIni(u8 Copy_u8PortID)
{
    // Set all pins of the port as output
    DIO_voidSetPortDirection(Copy_u8PortID, DIO_PORT_OUTPUT);
}

// Turn the LED on by setting the pin high
void LED_voidSetLedOn(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Set the pin value to high to turn the LED on
    DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_HIGH_OUTPUT);
}

// Turn the LED off by setting the pin low
void LED_voidSetLedOff(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Set the pin value to low to turn the LED off
    DIO_voidSetPinValue(Copy_u8PortID, Copy_u8PinID, DIO_LOW_OUTPUT);
}

// Toggle the LED state (on to off or off to on)
void LED_voidSetToggleLed(u8 Copy_u8PortID , u8 Copy_u8PinID)
{
    // Toggle the pin value to alternate the LED state
    DIO_voidTogglePin(Copy_u8PortID, Copy_u8PinID);
}

// Turn on all LEDs in the port by setting the port value to VCC (255)
void LED_voidSetPortLedOn(u8 Copy_u8PortID)
{
    // Set all pins in the port to high (255) to turn all LEDs on
    DIO_voidPortValue(Copy_u8PortID, VCC);
}

// Turn off all LEDs in the port by setting the port value to GROUND (0)
void LED_voidSetPortLedOff(u8 Copy_u8PortID)
{
    // Set all pins in the port to low (0) to turn all LEDs off
    DIO_voidPortValue(Copy_u8PortID, GROUND);
}
