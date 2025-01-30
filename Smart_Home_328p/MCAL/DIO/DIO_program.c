/*********************************************************/
/* Component : DIO                                       */
/* File      : DIO_programe.h                            */
/* Author    : Ahmed Hegazy                              */
/* Date      : 25 . 4 . 2024                             */
/* Version   : V1.0                                      */
/*********************************************************/

/* Includes */
// Library layer
#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"

// DIO files
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"

/* Function to set the direction of a specific pin */
void DIO_voidSetPinDirection(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinDirection)
{
    switch (Copy_u8PinDirection)
    {
    case DIO_PIN_OUTPUT:
        switch (Copy_u8PortID)
        {
        case DIO_PORTB:
            SET_BIT(DDRB, Copy_u8PinID);
            break;
        case DIO_PORTC:
            SET_BIT(DDRC, Copy_u8PinID);
            break;
        case DIO_PORTD:
            SET_BIT(DDRD, Copy_u8PinID);
            break;
        }
        break;

    case DIO_PIN_INPUT_FLOAT:
        switch (Copy_u8PortID)
        {
        case DIO_PORTB:
            CLR_BIT(DDRB, Copy_u8PinID);
            break;
        case DIO_PORTC:
            CLR_BIT(DDRC, Copy_u8PinID);
            break;
        case DIO_PORTD:
            CLR_BIT(DDRD, Copy_u8PinID);
            break;
        }
        break;

    case DIO_PIN_INPUT_PULL_UP:
        switch (Copy_u8PortID)
        {
        case DIO_PORTB:
            CLR_BIT(DDRB, Copy_u8PinID);
            SET_BIT(PORTB, Copy_u8PinID);
            break;
        case DIO_PORTC:
            CLR_BIT(DDRC, Copy_u8PinID);
            SET_BIT(PORTC, Copy_u8PinID);
            break;
        case DIO_PORTD:
            CLR_BIT(DDRD, Copy_u8PinID);
            SET_BIT(PORTD, Copy_u8PinID);
            break;
        }
        break;
    }
}

/* Function to set the direction of an entire port */
void DIO_voidSetPortDirection(u8 Copy_u8PortID, u8 Copy_u8PortDirection)
{
    switch (Copy_u8PortID)
    {
    case DIO_PORTB:
        DDRB = Copy_u8PortDirection;
        break;
    case DIO_PORTC:
        DDRC = Copy_u8PortDirection;
        break;
    case DIO_PORTD:
        DDRD = Copy_u8PortDirection;
        break;
    }
}

/* Function to set the value of a specific pin */
void DIO_voidSetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID, u8 Copy_u8PinValue)
{
    switch (Copy_u8PinValue)
    {
    case DIO_HIGH_OUTPUT:
        switch (Copy_u8PortID)
        {
        case DIO_PORTB:
            SET_BIT(PORTB, Copy_u8PinID);
            break;
        case DIO_PORTC:
            SET_BIT(PORTC, Copy_u8PinID);
            break;
        case DIO_PORTD:
            SET_BIT(PORTD, Copy_u8PinID);
            break;
        }
        break;

    case DIO_LOW_OUTPUT:
        switch (Copy_u8PortID)
        {
        case DIO_PORTB:
            CLR_BIT(PORTB, Copy_u8PinID);
            break;
        case DIO_PORTC:
            CLR_BIT(PORTC, Copy_u8PinID);
            break;
        case DIO_PORTD:
            CLR_BIT(PORTD, Copy_u8PinID);
            break;
        }
        break;
    }
}

/* Function to get the value of a specific pin */
u8 DIO_u8GetPinValue(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
    u8 Local_u8BitValue = 0;
    switch (Copy_u8PortID)
    {
    case DIO_PORTB:
        Local_u8BitValue = GET_BIT(PINB, Copy_u8PinID);
        break;
    case DIO_PORTC:
        Local_u8BitValue = GET_BIT(PINC, Copy_u8PinID);
        break;
    case DIO_PORTD:
        Local_u8BitValue = GET_BIT(PIND, Copy_u8PinID);
        break;
    }
    return Local_u8BitValue;
}

/* Function to toggle a specific pin */
void DIO_voidTogglePin(u8 Copy_u8PortID, u8 Copy_u8PinID)
{
    switch (Copy_u8PortID)
    {
    case DIO_PORTB:
        TGL_BIT(PORTB, Copy_u8PinID);
        break;
    case DIO_PORTC:
        TGL_BIT(PORTC, Copy_u8PinID);
        break;
    case DIO_PORTD:
        TGL_BIT(PORTD, Copy_u8PinID);
        break;
    }
}

/* Function to set the value of an entire port */
void DIO_voidPortValue(u8 Copy_u8PortID, u8 Copy_u8PortValue)
{
    switch (Copy_u8PortID)
    {
    case DIO_PORTB:
        PORTB = Copy_u8PortValue;
        break;
    case DIO_PORTC:
        PORTC = Copy_u8PortValue;
        break;
    case DIO_PORTD:
        PORTD = Copy_u8PortValue;
        break;
    }
}
