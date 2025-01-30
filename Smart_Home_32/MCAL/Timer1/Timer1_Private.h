#ifndef TIMER1_PRIVATE_H
#define TIMER1_PRIVATE_H

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

#endif
