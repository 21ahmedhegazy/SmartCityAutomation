/************************************/
/* Component : DIO                  */
/* File      : DIO_Program.c        */
/* Author    : Ahmed Hegazy          */
/* Date 	 : 15/7/2023            */
/* Version 	 : V1.0                 */
/************************************/

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "DIO_Register.h"
#include "DIO_Interface.h"




void DIO_voidSetPinDirection   (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8DIRECTION)
{
	if ((Copy_u8PORT <= PORTD )&&(Copy_u8PIN <= PIN7))
	{
	if (Copy_u8DIRECTION==OUTPUT)
	{
		switch(Copy_u8PORT)
		{
			case PORTA: SET_BIT(DDRA_REGISTER,Copy_u8PIN); break;
			case PORTB: SET_BIT(DDRB_REGISTER,Copy_u8PIN); break;
			case PORTC: SET_BIT(DDRC_REGISTER,Copy_u8PIN); break;
			case PORTD: SET_BIT(DDRD_REGISTER,Copy_u8PIN); break;

		}

	}
	else if (Copy_u8DIRECTION==INPUT)
	{
		switch(Copy_u8PORT)
		{
			case PORTA: CLR_BIT(DDRA_REGISTER,Copy_u8PIN); break;
			case PORTB: CLR_BIT(DDRB_REGISTER,Copy_u8PIN); break;
			case PORTC: CLR_BIT(DDRC_REGISTER,Copy_u8PIN); break;
			case PORTD: CLR_BIT(DDRD_REGISTER,Copy_u8PIN); break;

		}
	}
	else if (Copy_u8DIRECTION==INPUT_PULL_UP)
	{
		switch(Copy_u8PORT)
		{
			case PORTA : CLR_BIT(DDRA_REGISTER , Copy_u8PIN);
			  	  	  	 SET_BIT(PORTA_REGISTER , Copy_u8PIN);
			  	  	  	 break ;

			case PORTB : CLR_BIT(DDRB_REGISTER  , Copy_u8PIN);
				      	 SET_BIT(PORTB_REGISTER , Copy_u8PIN);
				      	 break ;

			case PORTC : CLR_BIT(DDRC_REGISTER  , Copy_u8PIN);
						 SET_BIT(PORTC_REGISTER , Copy_u8PIN);
						 break ;

			case PORTD : CLR_BIT(DDRD_REGISTER  , Copy_u8PIN);
						 SET_BIT(PORTD_REGISTER , Copy_u8PIN);
						 break ;
		}
	}
	}
}

void DIO_voidSetPortDirection  (u8 Copy_u8PORT , u8 Copy_u8DIRECTION)
{
	if (Copy_u8PORT <= PORTD&&Copy_u8PORT >= PORTA )
	{
		if (Copy_u8DIRECTION==PORT_OUTPUT)
		{
			switch(Copy_u8PORT)
			{
				case PORTA: DDRA_REGISTER = PORT_OUTPUT; break;
				case PORTB: DDRB_REGISTER = PORT_OUTPUT; break;
				case PORTC: DDRC_REGISTER = PORT_OUTPUT; break;
				case PORTD: DDRD_REGISTER = PORT_OUTPUT; break;

			}

		}
		else if (Copy_u8DIRECTION==PORT_INPUT)
		{
			switch(Copy_u8PORT)
			{
			case PORTA: DDRA_REGISTER = PORT_INPUT; break;
			case PORTB: DDRB_REGISTER = PORT_INPUT; break;
			case PORTC: DDRC_REGISTER = PORT_INPUT; break;
			case PORTD: DDRD_REGISTER = PORT_INPUT; break;

			}
		}
		else
		{
			switch(Copy_u8PORT)
			{
			case PORTA: DDRA_REGISTER = Copy_u8DIRECTION; break;
			case PORTB: DDRB_REGISTER = Copy_u8DIRECTION; break;
			case PORTC: DDRC_REGISTER = Copy_u8DIRECTION; break;
			case PORTD: DDRD_REGISTER = Copy_u8DIRECTION; break;

			}
		}

		}
	}

void DIO_voidSetPinValue       (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8VALUE)
{
	if ((Copy_u8PORT <= PORTD )&&(Copy_u8PIN <= PIN7))
	{
		if(Copy_u8VALUE == HIGH)
		{
			switch(Copy_u8PORT)
			{
			case PORTA: SET_BIT(PORTA_REGISTER,Copy_u8PIN); break;
			case PORTB: SET_BIT(PORTB_REGISTER,Copy_u8PIN); break;
			case PORTC: SET_BIT(PORTC_REGISTER,Copy_u8PIN); break;
			case PORTD: SET_BIT(PORTD_REGISTER,Copy_u8PIN); break;

			}
		}
		else if (Copy_u8VALUE == LOW)
		{
			switch(Copy_u8PORT)
			{
			case PORTA: CLR_BIT(PORTA_REGISTER,Copy_u8PIN); break;
			case PORTB: CLR_BIT(PORTB_REGISTER,Copy_u8PIN); break;
			case PORTC: CLR_BIT(PORTC_REGISTER,Copy_u8PIN); break;
			case PORTD: CLR_BIT(PORTD_REGISTER,Copy_u8PIN); break;
			}
			}
		else
		{
			switch(Copy_u8PORT)
			{
			case PORTA: PORTA_REGISTER = Copy_u8VALUE; break;
			case PORTB: PORTB_REGISTER = Copy_u8VALUE; break;
			case PORTC: PORTC_REGISTER = Copy_u8VALUE; break;
			case PORTD: PORTD_REGISTER = Copy_u8VALUE; break;

			}
		}
	}
}

void DIO_voidSetPortValue       (u8 Copy_u8PORT ,  u8 Copy_u8VALUE)
{
	switch(Copy_u8PORT)
	{
	case PORTA: PORTA_REGISTER  = Copy_u8VALUE; break;
	case PORTB: PORTB_REGISTER  = Copy_u8VALUE; break;
	case PORTC: PORTC_REGISTER  = Copy_u8VALUE; break;
	case PORTD: PORTD_REGISTER  = Copy_u8VALUE; break;
	}
}

void DIO_voidClearPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	if ((Copy_u8PORT <= PORTD )&&(Copy_u8PIN <= PIN7))
	{
		switch(Copy_u8PORT)
		{
		case PORTA: CLR_BIT(PORTA_REGISTER,Copy_u8PIN); break;
		case PORTB: CLR_BIT(PORTB_REGISTER,Copy_u8PIN); break;
		case PORTC: CLR_BIT(PORTC_REGISTER,Copy_u8PIN); break;
		case PORTD: CLR_BIT(PORTD_REGISTER,Copy_u8PIN); break;
		}
	}

}

void DIO_voidClearPortValue    (u8 Copy_u8PORT )
{
	if (Copy_u8PORT <= PORTD&&Copy_u8PORT >= PORTA )
	{
		switch(Copy_u8PORT)
		{
		case PORTA: PORTA_REGISTER  = PORT_LOW; break;
		case PORTB: PORTB_REGISTER  = PORT_LOW; break;
		case PORTC: PORTC_REGISTER  = PORT_LOW; break;
		case PORTD: PORTD_REGISTER  = PORT_LOW; break;
		}
	}
}

void DIO_voidTogglePinValue    (u8 Copy_u8PORT , u8 Copy_u8PIN)
{
	if ((Copy_u8PORT <= PORTD )&&(Copy_u8PIN <= PIN7))
	{

		switch(Copy_u8PORT)
		{
		case PORTA: TOGGLE_Bit(PORTA_REGISTER,Copy_u8PIN); break;
		case PORTB: TOGGLE_Bit(PORTB_REGISTER,Copy_u8PIN); break;
		case PORTC: TOGGLE_Bit(PORTC_REGISTER,Copy_u8PIN); break;
		case PORTD: TOGGLE_Bit(PORTD_REGISTER,Copy_u8PIN); break;

		}


}
}

void DIO_voidTogglePortValue    (u8 Copy_u8PORT )
{
	if ((Copy_u8PORT <= PORTD )&&(Copy_u8PORT >= PORTA ))
	{

		switch(Copy_u8PORT)
		{
		case PORTA: TOGGLE_PORT(PORTA_REGISTER); break;
		case PORTB: TOGGLE_PORT(PORTB_REGISTER); break;
		case PORTC: TOGGLE_PORT(PORTC_REGISTER); break;
		case PORTD: TOGGLE_PORT(PORTD_REGISTER); break;

		}


}
}

u8   DIO_u8GetPinValue         (u8 Copy_u8PORT , u8 Copy_u8PIN )
{
u8 Local_u8Result;
if ((Copy_u8PORT <= PORTD )&&(Copy_u8PIN <= PIN7))
	{
		switch(Copy_u8PORT)
		{
			case PORTA: Local_u8Result=GET_BIT(PINA_REGISTER,Copy_u8PIN); break;
			case PORTB: Local_u8Result=GET_BIT(PINB_REGISTER,Copy_u8PIN); break;
			case PORTC: Local_u8Result=GET_BIT(PINC_REGISTER,Copy_u8PIN); break;
			case PORTD: Local_u8Result=GET_BIT(PIND_REGISTER,Copy_u8PIN); break;

		}


	}

return Local_u8Result;

}

u8   DIO_u8GetPortValue        (u8 Copy_u8PORT )
{
	u8 Local_u8Result;
	if ((Copy_u8PORT <= PORTD)&&(Copy_u8PORT >= PORTA) )
		{
			switch(Copy_u8PORT)
			{
				case PORTA: Local_u8Result=PINA_REGISTER; break;
				case PORTB: Local_u8Result=PINB_REGISTER; break;
				case PORTC: Local_u8Result=PINC_REGISTER; break;
				case PORTD: Local_u8Result=PIND_REGISTER; break;
			}
		}

	return Local_u8Result;
}
