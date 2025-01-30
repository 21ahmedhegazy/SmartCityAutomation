/*
 * PRIVATE.h
 *
 *  Created on: Aug 10, 2022
 *      Author: Hegazy
 */

#ifndef _UART_PRIVATE_H
#define _UART_PRIVATE_H

#define UDR *((volatile u8*) 0x2c)

#define UCSRA *((volatile u8*) 0x2B)
#define UCSRA_RXC  7
#define UCSRA_TXC  6
#define UCSRA_UDRE 5
#define UCSRA_FE   4
#define UCSRA_DOR  3
#define UCSRA_PE   2
#define UCSRA_U2X  1
#define UCSRA_MPCM 0

#define UCSRB *((volatile u8*) 0x2A)
#define UCSRB_RXCIE  7
#define UCSRB_TXCIE  6
#define UCSRB_UDREIE 5
#define UCSRB_RXEN   4
#define UCSRB_TXEN   3
#define UCSRB_UCSZ2  2
#define UCSRB_RX88   1
#define UCSRB_TX88   0

#define UCSRC *((volatile u8*) 0x40)
#define UCSRC_URSEL  7
#define UCSRC_UMSEL  6
#define UCSRC_UPM1   5
#define UCSRC_UPM0   4
#define UCSRC_USBS   3
#define UCSRC_UCSZ1  2
#define UCSRC_UCSZ2   1
#define UCSRC_UCPOL   0

#define UBRRL *((volatile u8*) 0x29)

#endif /* UAUART_PRIVATE_H_*/
