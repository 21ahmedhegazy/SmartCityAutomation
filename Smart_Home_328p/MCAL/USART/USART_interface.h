/*********************************************************/
/* Component : USART                                      */
/* File      : USART_interface.h                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 21 . 9 . 2023                             */
/* Version   : V1.0                                      */


#ifndef MCAL_USART_USART_INTERFACE_H_
#define MCAL_USART_USART_INTERFACE_H_

// Initialize UART in Asynchronous 8-bit mode
void USART_voidAsync_8BIT_Init(void);

// Send data synchronously
void USART_voidSendDataSync(u8 Copy_u8Data);

// Send data asynchronously
void USART_voidSendDataAsync(u8 Copy_u8Data, void(*Copy_ptrFunction)(void));

// Send string synchronously
void USART_voidSendStringSync(char * Copy_ptrToString);

// Receive data synchronously
u8 USART_u8ReceiveDataSync(void);

// Receive data asynchronously
void USART_voidReceiveDataAsync(u8 *Copy_u8ReceiveData, void(*Copy_ptrFunction)(void));

// Send number (unsigned 32-bit) synchronously
void USART_voidSendNumber(u32 copy_u32Number);

#endif /* MCAL_USART_USART_INTERFACE_H_ */
