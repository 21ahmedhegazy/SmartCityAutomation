/*********************************************************/
/* Component : ADC                                      */
/* File      : ADC_private.h                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

// Channel Mask for Clearing
#define CHANNEL_MASK 0b11100000

// ADC Registers for ATmega328P
#define ADMUX     (*((volatile u8 *)(0x7C)))  // ADC Multiplexer Selection Register
#define ADCSRA    (*((volatile u8 *)(0x7A)))  // ADC Control and Status Register A
#define ADCL      (*((volatile u8 *)(0x78)))  // ADC Data Register Low Byte
#define ADCH      (*((volatile u8 *)(0x79)))  // ADC Data Register High Byte
#define ADC       (*((volatile u16 *)(0x78))) // ADC Data Register
#define ADCSRB    (*((volatile u8 *)(0x7B)))  // ADC Control and Status Register B

// Bit Positions for ADMUX
#define ADMUX_REFS1    7
#define ADMUX_REFS0    6
#define ADMUX_ADLAR    5

// Bit Positions for ADCSRA
#define ADCSRA_ADEN    7
#define ADCSRA_ADSC    6
#define ADCSRA_ADATE   5
#define ADCSRA_ADIF    4
#define ADCSRA_ADIE    3
#define ADCSRA_ADPS2   2
#define ADCSRA_ADPS1   1
#define ADCSRA_ADPS0   0

#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
