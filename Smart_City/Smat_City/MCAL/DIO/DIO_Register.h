/************************************/
/* File      : DIO_Register.h       */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V1.0                 */
/************************************/

#ifndef  MCAL_DIO_DIO_Register_H_
#define  MCAL_DIO_DIO_Register_H_

/* Group A Registers */
#define PORTA_REGISTER *((volatile u8*)0X3B)
#define DDRA_REGISTER  *((volatile u8*)0X3A)
#define PINA_REGISTER  *((volatile u8*)0X39)

/* Group B Registers */
#define PORTB_REGISTER *((volatile u8*)0X38)
#define DDRB_REGISTER  *((volatile u8*)0X37)
#define PINB_REGISTER  *((volatile u8*)0X36)

/* Group C Registers */
#define PORTC_REGISTER *((volatile u8*)0X35)
#define DDRC_REGISTER  *((volatile u8*)0X34)
#define PINC_REGISTER  *((volatile u8*)0X33)

/* Group D Registers */
#define PORTD_REGISTER *((volatile u8*)0X32)
#define DDRD_REGISTER  *((volatile u8*)0X31)
#define PIND_REGISTER  *((volatile u8*)0X30)

#endif
