/*********************************************************/
/* File      : TIMER_Private.h                           */
/* Author    : Ahmed Hegazy                              */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

/*****************Private bits*****************/
//TIMER-COUNTER0

#define TIMER0_TCCR0      *((volatile u8*)(0x53))
#define TCCR0_WGM0                 6  //two bits for mode of timer0
#define TCCR0_WGM1                 3
#define TCCR0_COM1                 5  //two bits for behavior of OC0 pin
#define TCCR0_COM0                 4
#define TCCR0_CS2				   2
#define TCCR0_CS1				   1
#define TCCR0_CS0				   0

#define TIMER0_TCNT0      *((volatile u8*)(0x52))
#define TIMER0_OCR0       *((volatile u8*)(0x5C))

#define TIMSK             *((volatile u8*)(0x59))
#define TIMSK_TOIE0                0  //timer0 over flow interrupt enable
#define TIMSK_OCIE0                1  //timer0 compare match interrupt enable

#define TIFR	          *((volatile u8*)(0x58))
#define TIFR_TOV0                  0  //timer0 over flow interrupt flag
#define TIFR_OCF0                  1  //timer0 compare match interrupt flag


#define TCCR1A  *((volatile u8*)(0x4F))
#define TCCR1B  *((volatile u8*)(0x4E))
#define TCNT1H  *((volatile u8*)(0x4D))
#define TCNT1L  *((volatile u8*)(0x4C))
#define TCNT1   *((volatile u16*)(0x4C))

#define OCR1AH  *((volatile u8*) (0x4B))
#define OCR1AL  *((volatile u8*) (0x4A))
#define OCR1A   *((volatile u16*)(0x4A))

#define OCR1BH  *((volatile u8*) (0x49))
#define OCR1BL  *((volatile u8*) (0x48))
#define OCR1B   *((volatile u16*)(0x48))

#define ICR1H  *((volatile u8*)(0x47))
#define ICR1L  *((volatile u8*)(0x46))
#define ICR1  *((volatile u16*)(0x46))

#define TIMSK  *((volatile u8*)(0x59))
#define TIFR  *((volatile u8*)(0x58))

#define CLK_MASK 0b11111000

//TCCR1A
#define WGM10   0
#define WGM11   1
#define FOC1B   2
#define FOC1A   3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

//TCCR1B

#define CS10   0
#define CS11   1
#define CS12   2
#define WGM12  3
#define WGM13  4

#define ICES1  6
#define ICNC1  7

//TIMSK
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5

// Define the TCCR2 register and its bits
#define TCCR2   *((volatile u8*)(0x45)) // Timer/Counter Control Register
#define WGM20   6 // Waveform Generation Mode bit 0
#define WGM21   3 // Waveform Generation Mode bit 1
#define COM21   5 // Compare Output Mode bit 1
#define COM20   4 // Compare Output Mode bit 0
#define CS22    2 // Clock Select bit 2
#define CS21    1 // Clock Select bit 1
#define CS20    0 // Clock Select bit 0

#define TIMER2_OCR2   *((volatile u8*)(0x43))// Output Compare Register
#define TCNT2   *((volatile u8*)(0x44)) // Timer/Counter Register
#define TIMSK   *((volatile u8*)(0x59)) // Timer Interrupt Mask Register
#define TIFR    *((volatile u8*)(0x58)) // Timer Interrupt Flag Register

#endif
