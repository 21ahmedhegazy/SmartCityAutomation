/*********************************************************/
/* Component : DIO                                       */
/* File      : DIO_private.h                             */
/* Author    : Ahmed Hegazy                              */
/* Date      : 25 . 4 . 2024                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_DIO_DIO_PRIVATE_H_
#define MCAL_DIO_DIO_PRIVATE_H_

// Register addresses for ATmega328P
#define DDRB  *((volatile u8 *)(0x24))
#define DDRC  *((volatile u8 *)(0x27))
#define DDRD  *((volatile u8 *)(0x2A))

#define PORTB  *((volatile u8 *)(0x25))
#define PORTC  *((volatile u8 *)(0x28))
#define PORTD  *((volatile u8 *)(0x2B))

#define PINB   *((volatile u8 *)(0x23))
#define PINC   *((volatile u8 *)(0x26))
#define PIND   *((volatile u8 *)(0x29))

#endif /* MCAL_DIO_DIO_PRIVATE_H_ */
