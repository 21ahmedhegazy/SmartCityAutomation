/*
 * USART_INT.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hegazy
 */

#ifndef _UART_INTERFACE_H
#define _UART_INTERFACE_H

void UART_voidInit (void);

void UART_voidSendDataSync(u8 Copy_u8Data );
void UART_voidSendDataAsync(u8 Copy_u8Data , void(*Copy_ptrFunction)(void));

void UART_voidSendStringSync(char * Copy_ptrToString);
void UART_voidSendNumber(u32 copy_u32Number);

u8 UART_u8ReceiveDataSync(void);
void UART_voidReceiveDataAsync(u8 *Copy_u8ReceiveData , void(*Copy_ptrFunction)(void));

u8 UART_u8IsDataAvailable(void);



#endif /* UAUART_INTERFACE_H_*/
