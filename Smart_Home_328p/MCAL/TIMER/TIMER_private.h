/*********************************************************/
/* Component : TIMER                                      */
/* File      : TIMER_private.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 5 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_TIMER_TIMER_PRIVATE_H_
#define MCAL_TIMER_TIMER_PRIVATE_H_

/******************* Configuration Options *****************/

#define NORMAL_MODE               1
#define CTC_MODE                  2
#define FAST_PWM                  3
#define PHASE_CORRECT_PWM         4

/******************* Private Bits *****************/

// TIMER-COUNTER0 (8-bit)
#define TIMER0_TCCR0      *((volatile u8 *)(0x44))
#define TCCR0_WGM0                 0  // Timer0 Mode Bit 0
#define TCCR0_WGM1                 1  // Timer0 Mode Bit 1
#define TCCR0_COM1                 7  // Timer0 Compare Match Mode (Non-Inverted PWM)
#define TCCR0_COM0                 6  // Timer0 Compare Match Mode (Non-Inverted PWM)

#define TIMER0_TCNT0      *((volatile u8 *)(0x46)) // Timer0 Counter Register
#define TIMER0_OCR0       *((volatile u8 *)(0x47)) // Timer0 Output Compare Register

// Timer Interrupts
#define TIMSK             *((volatile u8 *)(0x6E))
#define TIMSK_TOIE0                0  // Timer0 Overflow Interrupt Enable
#define TIMSK_OCIE0                1  // Timer0 Compare Match Interrupt Enable

#define TIFR               *((volatile u8 *)(0x35))
#define TIFR_TOV0                  0  // Timer0 Overflow Interrupt Flag
#define TIFR_OCF0                  1  // Timer0 Compare Match Interrupt Flag


// TIMER-COUNTER1 (16-bit)
#define TIMER1_TCCR1A     *((volatile u8 *)(0x80)) // Timer1 Control Register A
#define TCCRA_COM1A1       7
#define TCCRA_COM1A0       6
#define TCCRA_COM1B1       5
#define TCCRA_COM1B0       4



#define TIMER1_TCCR1B     *((volatile u8 *)(0x81)) // Timer1 Control Register B
#define TIMER1_TCNT1      *((volatile u16 *)(0x84)) // Timer1 Counter Register (16-bit)
#define TIMER1_OCR1A      *((volatile u16 *)(0x88)) // Timer1 Output Compare Register A (16-bit)
#define TIMER1_OCR1B      *((volatile u16 *)(0x8A)) // Timer1 Output Compare Register B (16-bit)
#define TIMER1_ICR1       *((volatile u16 *)(0x86)) // Timer1 Input Capture Register (16-bit)

/******************* PRESCALER MASK ********************/
#define PRESCALER_MASK         0b11111000  // Mask for prescaler bits (bits 0-2)
#define TIMER0_NO_CLOCK        0
#define TIMER0_PRESCALER_1     1
#define TIMER0_PRESCALER_8     2
#define TIMER0_PRESCALER_64    3
#define TIMER0_PRESCALER_256   4
#define TIMER0_PRESCALER_1024  5

#define TIMER1_NO_CLOCK        0
#define TIMER1_PRESCALER_1     1
#define TIMER1_PRESCALER_8     2
#define TIMER1_PRESCALER_64    3
#define TIMER1_PRESCALER_256   4
#define TIMER1_PRESCALER_1024  5

#endif /* MCAL_TIMER_TIMER_PRIVATE_H_ */
