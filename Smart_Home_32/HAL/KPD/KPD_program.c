/*********************************************************/
/* Component : KPD                                       */
/* File      : KPD_program.c                             */
/* Author    : Hegazy                                     */
/* Date      : 28 . 7 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

//library layer
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

//MCAL
#include "../../MCAL/DIO/DIO_interface.h"

//keypad files
#include "KPD_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"
#include <util/delay.h>

/*************************************************************************/
/***************************Functions' implementation*********************/
/*************************************************************************/

void KPD_voidInit(void)
{
	//Set the direction of rows to be input pull up
	DIO_voidSetPinDirection(KPD_PORT , ROW0_PIN , INPUT_PULL_UP);
	DIO_voidSetPinDirection(KPD_PORT , ROW1_PIN , INPUT_PULL_UP);
	DIO_voidSetPinDirection(KPD_PORT , ROW2_PIN , INPUT_PULL_UP);
	DIO_voidSetPinDirection(KPD_PORT , ROW3_PIN , INPUT_PULL_UP);


	//Set the direction of columns to be output
	DIO_voidSetPinDirection(KPD_PORT , COL0_PIN , OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , COL1_PIN , OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , COL2_PIN , OUTPUT);
	DIO_voidSetPinDirection(KPD_PORT , COL3_PIN , OUTPUT);

	//Set the value of columns to be high output
	DIO_voidSetPinValue(KPD_PORT , COL0_PIN , HIGH);
	DIO_voidSetPinValue(KPD_PORT , COL1_PIN , HIGH);
	DIO_voidSetPinValue(KPD_PORT , COL2_PIN , HIGH);
	DIO_voidSetPinValue(KPD_PORT , COL3_PIN , HIGH);

}

u8 KPD_u8GetPressedKey(void)
{
	//to save the state of the row either 0 or 1
	u8 Local_u8SwitchState ;

	//The value of any pressed key , initially configurable
	u8 Local_u8PressedKey = NO_PRESSED_KEY ;

	//Set the value of keys to be configurable
	u8 Local_u8Values[ROWS_NO][COLS_NO]=VALUES ;

	//iterators to loop over columns and rows
	u8 Local_u8ColIterator = 0;
	u8 Local_u8RowIterator = 0;

	//array to save the configurations of the columns
	u8 Local_au8Cols[COLS_NO]={COL0_PIN,COL1_PIN,COL2_PIN,COL3_PIN};

	//array to save the configurations of the rows
	u8 Local_au8Rows[ROWS_NO]={ROW0_PIN,ROW1_PIN,ROW2_PIN,ROW3_PIN};

	//loop over columns to activate one by one
	for(Local_u8ColIterator=0 ; Local_u8ColIterator<COLS_NO ; Local_u8ColIterator++)
	{
		//activate the target column
		DIO_voidSetPinValue(KPD_PORT ,Local_au8Cols[Local_u8ColIterator], LOW);

		//loop over the rows to check for pressed keys
		for(Local_u8RowIterator=0 ; Local_u8RowIterator<ROWS_NO ; Local_u8RowIterator++)
		{
			//read the row value
			Local_u8SwitchState =DIO_u8GetPinValue(KPD_PORT , Local_au8Rows[Local_u8RowIterator]);

			//in case of a pressed key
			if(Local_u8SwitchState==0)
			{
				//Get the value of the pressed key
				Local_u8PressedKey = Local_u8Values[Local_u8RowIterator][Local_u8ColIterator];
            while(Local_u8SwitchState==0){
    			Local_u8SwitchState =DIO_u8GetPinValue(KPD_PORT , Local_au8Rows[Local_u8RowIterator]);
            }
				_delay_ms(5);
				return Local_u8PressedKey ;
			}
		}
		//Deactivate the target column
		DIO_voidSetPinValue(KPD_PORT ,Local_au8Cols[Local_u8ColIterator], HIGH);
	}

	return Local_u8PressedKey ;
}
