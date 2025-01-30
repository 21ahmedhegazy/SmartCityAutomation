
/*
 * LCD_Program.c
 *
 *  Created on: Jul 21, 2023
 *      Author: Hegazy
 */
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_Interface.h"
#include "LCD_Config.h"
#include "LCD_Interface.h"
#include "LCD_Private.h"
#include "avr/delay.h"


/*
 -----------                   ----------
 | ATmega32  |                 |   LCD    |
 |           |                 |          |
 |        PD7|---------------->|D7        |
 |        PD6|---------------->|D6        |
 |        PD5|---------------->|D5        |
 |        PD4|---------------->|D4        |
 |        PD3|---------------->|D3        |
 |        PD2|---------------->|D2        |
 |        PD1|---------------->|D1        |
 |        PD0|---------------->|D0        |
 |           |                 |          |
 |        PA2|---------------->|E         |
 |        PA1|---------------->|RW        |
 |        PA0|---------------->|RS        |
 -----------                   ----------
 */

void LCD_voidInit(void)
{
	//Set direction of control pins -> RS , RW , EN to be output

	DIO_voidSetPinDirection(RS_PORT , RS_PIN , OUTPUT);

	DIO_voidSetPinDirection(RW_PORT , RW_PIN , OUTPUT);

	DIO_voidSetPinDirection(EN_PORT , EN_PIN , OUTPUT);

	//Set direction of data port to be output
	DIO_voidSetPortDirection(DATA_PORT , PORT_OUTPUT);

	_delay_ms(30);

	LCD_voidWriteCommand(Lcd_Home);
	_delay_ms(15);

	LCD_voidWriteCommand(Lcd_FunctionSet8bit);
	_delay_ms(1);

	LCD_voidWriteCommand(Lcd_DisplayOn);
	_delay_ms(1);

	LCD_voidWriteCommand(Lcd_Clear);
	_delay_ms(2);

	LCD_voidWriteCommand(Lcd_EntryMode);
	_delay_ms(2);
}

void LCD_voidWriteCommand (u8 Copy_u8Command)
{

	//1- Set RW pin to be write -> 0
	DIO_voidSetPinValue(RW_PORT, RW_PIN , LOW);

	//2- Set RS pin to send command -> 0
	DIO_voidSetPinValue(RS_PORT , RS_PIN , LOW);

	//3- Set the Cmd over data port
	DIO_voidSetPortValue(DATA_PORT , Copy_u8Command);

	//4- Set enable pin to be high for 2ms
	DIO_voidSetPinValue(EN_PORT , EN_PIN , HIGH);
	_delay_ms(2);

	//5- Set enable pin to be low again
	DIO_voidSetPinValue(EN_PORT , EN_PIN , LOW);
}

void LCD_voidWriteData (u8 Copy_u8Data)
{
	//1- Set RW pin to be write -> 0
	DIO_voidSetPinValue(RW_PORT, RW_PIN , LOW);

	//2- Set RS pin to send data -> 1
	DIO_voidSetPinValue(RS_PORT , RS_PIN , HIGH);

	//3- Set the data over data port
	DIO_voidSetPortValue(DATA_PORT , Copy_u8Data);

	//4- Set enable pin to be high for 2ms
	DIO_voidSetPinValue(EN_PORT , EN_PIN , HIGH);
	_delay_ms(2);

	//5- Set enable pin to be low again
	DIO_voidSetPinValue(EN_PORT , EN_PIN , LOW);
}

void LCD_voidWriteString(u8* Copy_pu8String )
{
	//local variable to iterate over string characters
	u8 Local_u8CharIterator = 0 ;

	//loop till getting to \0 character -> end of string
	while(Copy_pu8String[Local_u8CharIterator] != '\0')
	{
		//send the character to get displayed
		LCD_voidWriteData(Copy_pu8String[Local_u8CharIterator]) ;

		//move to the next character
		Local_u8CharIterator ++ ;


	}

}

void LCD_voidWriteStringTwoLine(u8* Copy_pu8String )
{
	//local variable to iterate over string characters
	u8 Local_u8CharIterator = 0 ;
    u8 Local_u8Pos = 1 ;
    u8 pos =0 ;
	//loop till getting to \0 character -> end of string
	while(Copy_pu8String[Local_u8CharIterator] != '\0')
	{
		//send the character to get displayed
		LCD_voidWriteData(Copy_pu8String[Local_u8CharIterator]) ;

		//move to the next character
		Local_u8CharIterator ++ ;
		Local_u8Pos++;
		if(Local_u8Pos > 16)
		{

			while(Copy_pu8String[Local_u8CharIterator] != '\0')
			{
			LCD_voidGOToXY(2,pos);
			LCD_voidWriteData(Copy_pu8String[Local_u8CharIterator]);
			Local_u8CharIterator ++ ;
			pos++;
			}
		}

	}
}

void LCD_voidGOToXY(u8 Copy_u8ROW ,u8 Copy_u8COL)
{
	if (((Copy_u8ROW <= 2 ) && (Copy_u8ROW > 0)) && ((Copy_u8COL > 0) && (Copy_u8COL <= 16)))
	{
		switch (Copy_u8ROW)
		{
		case 1 :LCD_voidWriteCommand(Copy_u8COL + 127);break;
		case 2 :LCD_voidWriteCommand(Copy_u8COL + 191);break;
		default:break;
		}
	}
}

void LCD_voidSendSpecialCharacter(u8 * Copy_pu8Pattern , u8 Copy_u8Location
								  ,u8 Copy_u8Row , u8 Copy_u8Col )
{
	/*An iterator to loop over pattern bytes*/
	u8 Local_u8PatternIterator = 0 ;

	//1. Set the address of the location in CGRAM
	u8 Local_u8CGRAMAddress = Copy_u8Location * 8 ;

	//2. Move the Address Counter to the target location
	LCD_voidWriteCommand(Local_u8CGRAMAddress + 64);

	//3. Set the target pattern into the Bytes of the CGRAM location
	for(Local_u8PatternIterator = 0 ; Local_u8PatternIterator < 7 ; Local_u8PatternIterator++)
	{
		LCD_voidWriteData(Copy_pu8Pattern[Local_u8PatternIterator]);
		//Address counter increments automatically
	}

	//4. Turning back to DDRAM
	LCD_voidGOToXY(Copy_u8Row , Copy_u8Col);

	//5. Order DDRAM to read the pattern from CGRAM and display it
	LCD_voidWriteData(Copy_u8Location);
}

void LCD_voidFree(u8 Copy_u8ROW ,u8 Copy_u8COL)
{
	LCD_voidGOToXY(Copy_u8ROW,Copy_u8COL);
	LCD_voidWriteData(128);
	LCD_voidGOToXY(Copy_u8ROW,Copy_u8COL);
}

void LCD_voidClearDisplay(void)
{
	LCD_voidWriteCommand(Lcd_Clear);
}

void LCD_voidWriteNumber(u32 copy_u32Number)
{
	u32 Local_u32Reverse = 1;
while(copy_u32Number != 0)
{
	Local_u32Reverse = Local_u32Reverse * 10 + copy_u32Number%10;
	copy_u32Number /= 10;

}
do
{

	LCD_voidWriteData((Local_u32Reverse%10) +'0');
	Local_u32Reverse /= 10;

}
while(Local_u32Reverse != 1);
}

/*switch(remainder)
	{
	case 0 :LCD_voidWriteData('0'); break;
	case 1 :LCD_voidWriteData('1'); break;
	case 2 :LCD_voidWriteData('2'); break;
	case 3 :LCD_voidWriteData('3'); break;
	case 4 :LCD_voidWriteData('4'); break;
	case 5 :LCD_voidWriteData('5'); break;
	case 6 :LCD_voidWriteData('6'); break;
	case 7 :LCD_voidWriteData('7'); break;
	case 8 :LCD_voidWriteData('8'); break;
	case 9 :LCD_voidWriteData('9'); break;

	}*/
