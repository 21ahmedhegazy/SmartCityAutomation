/*********************************************************/
/* Component : USART                                      */
/* File      : USART_private.h                             */
/* Author    : Ahmed Hegazy                                        */
/* Date      : 21 . 9 . 2023                             */
/* Version   : V1.0                                      */


#ifndef MCAL_USART_USART_PRIVATE_H_
#define MCAL_USART_USART_PRIVATE_H_

// Register Mapping for ATmega328P

#define UDR     *((volatile u8*)(0xC6))    // USART Data Register
#define UCSRA   *((volatile u8*)(0xC0))    // USART Control and Status Register A
#define RXC     7   // USART Receive Complete
#define TXC     6   // USART Transmit Complete
#define UDRE    5   // USART Data Register Empty
#define FE      4   // Frame Error
#define DOR     3   // Data OverRun
#define PE      2   // Parity Error
#define U2X     1   // Double USART Transmission Speed
#define MPCM    0   // Multi-processor Communication Mode

#define UCSRB   *((volatile u8*)(0xC1))    // USART Control and Status Register B
#define RXCIE   7   // USART Receive Complete Interrupt Enable
#define TXCIE   6   // USART Transmit Complete Interrupt Enable
#define UDRIE   5   // USART Data Register Empty Interrupt Enable
#define RXEN    4   // Receiver Enable
#define TXEN    3   // Transmitter Enable
#define UCSZ2   2   // Character Size Bit 2
#define RXB8    1   // Receive Data Bit 8
#define TXB8    0   // Transmit Data Bit 8

#define UCSRC   *((volatile u8*)(0xC2))    // USART Control and Status Register C
#define URSEL   7   // Register Select
#define UMSEL   6   // USART Mode Select
#define UPM1    5   // Parity Mode Bit 1
#define UPM0    4   // Parity Mode Bit 0
#define USBS    3   // Stop Bit Select
#define UCSZ1   2   // Character Size Bit 1
#define UCSZ0   1   // Character Size Bit 0
#define UCPOL   0   // Clock Polarity

#define UBRRL   *((volatile u8*)(0xC4))    // USART Baud Rate Register (Low Byte)
#define UBRRH   *((volatile u8*)(0xC5))    // USART Baud Rate Register (High Byte)

// Interrupt Vectors
#define USART_RX_vect      __vector_13  // Receive Complete Interrupt
#define USART_UDRE_vect    __vector_14  // Data Register Empty Interrupt
#define USART_TX_vect      __vector_15  // Transmit Complete Interrupt

#endif /* MCAL_USART_USART_PRIVATE_H_ */
