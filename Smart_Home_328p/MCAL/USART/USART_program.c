/*********************************************************/
/* Component : USART                                     */
/* File      : USART_program.c                           */
/* Author    : Ahmed Hegazy                                       */
/* Date      : 21 . 9 . 2023                             */
/* Version   : V1.0                                      */

#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"
#include "USART_config.h"
#include "USART_interface.h"
#include "USART_private.h"

u8 *Global_u8ReceiveData = NULL_PTR;
void (*Global_ptrFunctionRXcomplete)(void) = NULL_PTR;
void (*Global_ptrFunctionTXcomplete)(void) = NULL_PTR;
void (*Global_ptrFunctionDataRegEmpty)(void) = NULL_PTR;

// This function shall initialize UART
void USART_voidAsync_8BIT_Init(void)
{
    // Set UCSRC Register for 8-bit Asynchronous Mode, 1 Stop Bit, No Parity, 8 Data Bits
    UCSRC = 0b10000110;  // URSEL must be set to access UCSRC register

    // Set UCSZ2 = 0 (8-bit data)
    CLR_BIT(UCSRB, UCSZ2);

    // Set Baud Rate to 9600 for 8MHz clock (UBRR = 51)
    UBRRL = 51;  // Baud rate low byte
    UBRRH = 0;   // Baud rate high byte

    // Enable Receiver and Transmitter
    SET_BIT(UCSRB, RXEN);
    SET_BIT(UCSRB, TXEN);
}

// This function sends data synchronously
void USART_voidSendDataSync(u8 Copy_u8Data)
{
    // Wait for the Data Register to be empty (UDRE)
    while ((GET_BIT(UCSRA, UDRE)) == 0);

    // Write data to UDR register for transmission
    UDR = Copy_u8Data;

    // Wait until transmission is complete (TXC)
    while ((GET_BIT(UCSRA, TXC)) == 0);

    // Clear the transmission complete flag (TXC)
    SET_BIT(UCSRA, TXC);
}

// This function sends data asynchronously
void USART_voidSendDataAsync(u8 Copy_u8Data, void(*Copy_ptrFunction)(void))
{
    // Enable Transmit Complete Interrupt
    SET_BIT(UCSRB, TXCIE);

    // Set the callback function for TX Complete interrupt
    Global_ptrFunctionTXcomplete = Copy_ptrFunction;

    // Send the data
    UDR = Copy_u8Data;
}

// This function sends a string synchronously
void USART_voidSendStringSync(char * Copy_ptrToString)
{
    u8 Local_u8Iterator = 0;

    // Send each character in the string
    while (Copy_ptrToString[Local_u8Iterator] != '\0')
    {
        USART_voidSendDataSync(Copy_ptrToString[Local_u8Iterator]);
        Local_u8Iterator++;
    }
}

// This function receives data synchronously
u8 USART_u8ReceiveDataSync(void)
{
    // Wait until data is received (RXC)
    while ((GET_BIT(UCSRA, RXC)) == 0);

    // Return the received data
    return UDR;
}

// This function receives data asynchronously
void USART_voidReceiveDataAsync(u8 *Copy_u8ReceiveData, void(*Copy_ptrFunction)(void))
{
    // Enable Receive Complete Interrupt
    SET_BIT(UCSRB, RXCIE);

    // Set the callback function for RX Complete interrupt
    Global_ptrFunctionRXcomplete = Copy_ptrFunction;

    // Store the pointer to the received data
    Global_u8ReceiveData = Copy_u8ReceiveData;
}

// This function sends a number (unsigned 32-bit) synchronously
void USART_voidSendNumber(u32 copy_u32Number)
{
    u32 Local_u32Reverse = 1;

    // Reverse the number
    while (copy_u32Number != 0)
    {
        Local_u32Reverse = Local_u32Reverse * 10 + copy_u32Number % 10;
        copy_u32Number /= 10;
    }

    // Send each digit of the reversed number
    do
    {
        USART_voidSendDataSync((Local_u32Reverse % 10) + '0');
        Local_u32Reverse /= 10;
    } while (Local_u32Reverse != 1);
}

// USART RX Complete Interrupt Service Routine
void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
    // Store received data
    *Global_u8ReceiveData = UDR;

    // Call the callback function for RX complete
    if (Global_ptrFunctionRXcomplete != NULL_PTR)
    {
        Global_ptrFunctionRXcomplete();
    }
}

// USART TX Complete Interrupt Service Routine
void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
    // Call the callback function for TX complete
    if (Global_ptrFunctionTXcomplete != NULL_PTR)
    {
        Global_ptrFunctionTXcomplete();
    }
}
