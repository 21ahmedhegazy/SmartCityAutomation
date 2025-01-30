/************************************/
/* File      : LED_Program.c      */
/* Author    : Ahmed Hegazy          */
/* Version 	 : V1.0                 */
/************************************/
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LED_Interface.h"

void LED_voidLedInit            (u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	switch (Copy_u8PORT)
	{
	{
	case PORTA : DIO_voidSetPinDirection(PORTA,Copy_u8PIN,OUTPUT);break;
	case PORTB : DIO_voidSetPinDirection(PORTB,Copy_u8PIN,OUTPUT);break;
	case PORTC : DIO_voidSetPinDirection(PORTC,Copy_u8PIN,OUTPUT);break;
	case PORTD : DIO_voidSetPinDirection(PORTD,Copy_u8PIN,OUTPUT);break;
	}
}
}

void LED_voidPortLedInit     (u8 Copy_u8PORT )
{
	switch (Copy_u8PORT)
	{
	{
	case PORTA : DIO_voidSetPortDirection(PORTA,PORT_OUTPUT);break;
	case PORTB : DIO_voidSetPortDirection(PORTB,PORT_OUTPUT);break;
	case PORTC : DIO_voidSetPortDirection(PORTC,PORT_OUTPUT);break;
	case PORTD : DIO_voidSetPortDirection(PORTD,PORT_OUTPUT);break;
	}
	}
}

void LED_voidLedOn(u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Type)
{
	if(Copy_u8Type == VCC)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPinValue(PORTA,Copy_u8PIN,HIGH);break;
		case PORTB : DIO_voidSetPinValue(PORTB,Copy_u8PIN,HIGH);break;
		case PORTC : DIO_voidSetPinValue(PORTC,Copy_u8PIN,HIGH);break;
		case PORTD : DIO_voidSetPinValue(PORTD,Copy_u8PIN,HIGH);break;
		}
	}
	else if (Copy_u8Type == GROUND)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPinValue(PORTA,Copy_u8PIN,LOW);break;
		case PORTB : DIO_voidSetPinValue(PORTB,Copy_u8PIN,LOW);break;
		case PORTC : DIO_voidSetPinValue(PORTC,Copy_u8PIN,LOW);break;
		case PORTD : DIO_voidSetPinValue(PORTD,Copy_u8PIN,LOW);break;
		}
	}
}

void LED_voidLedOff    		 (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Type)
{
	if(Copy_u8Type == VCC)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPinValue(PORTA,Copy_u8PIN,LOW);break;
		case PORTB : DIO_voidSetPinValue(PORTB,Copy_u8PIN,LOW);break;
		case PORTC : DIO_voidSetPinValue(PORTC,Copy_u8PIN,LOW);break;
		case PORTD : DIO_voidSetPinValue(PORTD,Copy_u8PIN,LOW);break;
		}
	}
	else if (Copy_u8Type == GROUND)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPinValue(PORTA,Copy_u8PIN,HIGH);break;
	    case PORTB : DIO_voidSetPinValue(PORTB,Copy_u8PIN,HIGH);break;
		case PORTC : DIO_voidSetPinValue(PORTC,Copy_u8PIN,HIGH);break;
		case PORTD : DIO_voidSetPinValue(PORTD,Copy_u8PIN,HIGH);break;
		}
	}
}

void LED_voidPortLedOn 		 (u8 Copy_u8PORT ,  u8 Copy_u8Type)
{
	if(Copy_u8Type == VCC)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPortValue(PORTA,PORT_HIGH);break;
		case PORTB : DIO_voidSetPortValue(PORTB,PORT_HIGH);break;
		case PORTC : DIO_voidSetPortValue(PORTC,PORT_HIGH);break;
		case PORTD : DIO_voidSetPortValue(PORTD,PORT_HIGH);break;
		}
	}
	else if (Copy_u8Type == GROUND)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPortValue(PORTA,PORT_LOW);break;
		case PORTB : DIO_voidSetPortValue(PORTB,PORT_LOW);break;
		case PORTC : DIO_voidSetPortValue(PORTC,PORT_LOW);break;
		case PORTD : DIO_voidSetPortValue(PORTD,PORT_LOW);break;
		}
	}
}

void LED_voidPortLedOff 	 (u8 Copy_u8PORT ,  u8 Copy_u8Type)
{
	if(Copy_u8Type == VCC)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPortValue(PORTA,PORT_LOW);break;
		case PORTB : DIO_voidSetPortValue(PORTB,PORT_LOW);break;
		case PORTC : DIO_voidSetPortValue(PORTC,PORT_LOW);break;
		case PORTD : DIO_voidSetPortValue(PORTD,PORT_LOW);break;
		}
	}
	else if (Copy_u8Type == GROUND)
	{
		switch (Copy_u8PORT)
		{
		case PORTA : DIO_voidSetPortValue(PORTA,PORT_HIGH);break;
		case PORTB : DIO_voidSetPortValue(PORTB,PORT_HIGH);break;
		case PORTC : DIO_voidSetPortValue(PORTC,PORT_HIGH);break;
		case PORTD : DIO_voidSetPortValue(PORTD,PORT_HIGH);break;
		}
	}
}

void LED_voidLedToggle       (u8 Copy_u8PORT , u8 Copy_u8PIN  )
{
	switch (Copy_u8PORT)
	{
	case PORTA : DIO_voidTogglePinValue(PORTA,Copy_u8PIN);break;
	case PORTB : DIO_voidTogglePinValue(PORTB,Copy_u8PIN);break;
	case PORTC : DIO_voidTogglePinValue(PORTC,Copy_u8PIN);break;
	case PORTD : DIO_voidTogglePinValue(PORTD,Copy_u8PIN);break;
	}
}

void LED_voidPortLedToggle 	 (u8 Copy_u8PORT )
{
	switch (Copy_u8PORT)
	{
	case PORTA : DIO_voidTogglePortValue(PORTA);break;
	case PORTB : DIO_voidTogglePortValue(PORTB);break;
	case PORTC : DIO_voidTogglePortValue(PORTC);break;
	case PORTD : DIO_voidTogglePortValue(PORTD);break;
	}
}
