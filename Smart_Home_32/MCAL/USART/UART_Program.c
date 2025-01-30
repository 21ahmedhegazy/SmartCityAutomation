/*
 * PROG.C
 *
 *  Created on: Aug 10, 2022
 *      Author: Hegazy
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "UART_Interface.h"
#include "UART_Config.h"
#include "UART_Private.h"

u8 *Global_u8ReceiveData =NULL ;

void (*Global_ptrFunctionRXcomplete) (void) = NULL;
void (*Global_ptrFunctionTXcomplete) (void) = NULL;
void (*Global_ptrFunctionDataRegEmpty) (void) = NULL;

void UART_voidInit (void)
{
	//Set the mode to be transmitter and receiver at the same time
	   SET_BIT(UCSRB,UCSRB_RXEN);  //Enable transmission
	   SET_BIT(UCSRB,UCSRB_TXEN);  //Enable receiver

	//SEt character size to be 8 bit
	   CLR_BIT(UCSRB,UCSRB_UCSZ2);
	   UCSRC = (1<<UCSRC_UCSZ1) | (1<<UCSRC_UCSZ2) | (1<<UCSRC_URSEL);
	   UBRRL =51;

	// Set Baud rate to be 9600 bps
	   UBRRL =51;

	   //No parity bits
	   // 1 stop bit
}

void UART_voidSendDataSync(u8 Copy_u8Data )
{
	//1. make sure that the transmission buffer is empty
	while ((GET_BIT(UCSRA,UCSRA_UDRE)) == 0);
	//2.Write the data to get transmission
	UDR = Copy_u8Data;
	//3.Wait till the end of transmission
	while ((GET_BIT(UCSRA ,UCSRA_TXC)) == 0 );
	//4.Clear end of transmission flag
	SET_BIT(UCSRA ,UCSRA_TXC);
}

void UART_voidSendDataAsync(u8 Copy_u8Data , void(*Copy_ptrFunction)(void))
{

  //1.Enable TX intr
	SET_BIT(UCSRB,UCSRB_TXCIE);

	Global_ptrFunctionTXcomplete = Copy_ptrFunction;

	UDR = Copy_u8Data ;

}


void UART_voidSendStringSync(char * Copy_ptrToString)
{
	u8 Local_u8Iterator = 0 ;
	while(Copy_ptrToString[Local_u8Iterator] != '\0')
	{
		UART_voidSendDataSync(Copy_ptrToString[Local_u8Iterator]);
		Local_u8Iterator++;
	}

}

u8 UART_u8ReceiveDataSync(void)
{
	//1.Wait till the end of reception
	while ((GET_BIT(UCSRA ,UCSRA_RXC)) == 0 );
	//2. Get the received data -> the flag is cleared
	return UDR ;

}

void UART_voidSendNumber(u32 copy_u32Number)
{
	u32 Local_u32Reverse = 1;
while(copy_u32Number != 0)
{
	Local_u32Reverse = Local_u32Reverse * 10 + copy_u32Number%10;
	copy_u32Number /= 10;

}
do
{
	UART_voidSendDataSync((Local_u32Reverse%10) +'0');
	Local_u32Reverse /= 10;

}
while(Local_u32Reverse != 1);
}



void UART_voidReceiveDataAsync(u8 *Copy_u8ReceiveData , void(*Copy_ptrFunction)(void))
{

	  //1.Enable TX intr
		SET_BIT(UCSRB,UCSRB_RXCIE);

		Global_ptrFunctionRXcomplete =Copy_ptrFunction ;
        Global_u8ReceiveData = Copy_u8ReceiveData ;


}

// void UART_CallBackFunctoin(void (*Ptr)(void))
// {
//
// }
//
 //RX Complete
 void __vector_13(void)  __attribute__((signal));
 void __vector_13(void)
 {

	 		 *Global_u8ReceiveData =UDR ;
	 		Global_ptrFunctionRXcomplete();


 }
//
// //Data register empty
// void __vector_14(void)  __attribute__((signal));
// void __vector_14(void)
// {
//
// }
//
// //TX Complete
 void __vector_15(void)  __attribute__((signal));
 void __vector_15(void)
 {
 	 if (Global_ptrFunctionTXcomplete != NULL)
 	 {
 		 Global_ptrFunctionTXcomplete();
 	 }
 }

 u8 UART_u8IsDataAvailable(void) {
     return (UCSRA & (1 << UCSRA_RXC)) ? 1 : 0; // Return 1 if RXC bit is set, 0 otherwise
 }

