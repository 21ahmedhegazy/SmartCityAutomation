/*********************************************************/
/* File      : ADC_private.h                             */
/* Author    : Ahmed Hegazy                              */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_ADC_ADC_PRIVATE_H_
#define MCAL_ADC_ADC_PRIVATE_H_

// Definitions for ADC Registers (Memory Mapped I/O)
#define ADMUX      (*((volatile u8*)(0x27)))  // ADC Multiplexer Selection Register
#define ADCSRA     (*((volatile u8*)(0x26)))  // ADC Control and Status Register A
#define ADCL       (*((volatile u8*)(0x24)))  // ADC Data Register Low Byte
#define ADCH       (*((volatile u8*)(0x25)))  // ADC Data Register High Byte
#define ADC        (*((volatile u16*)(0x24))) // ADC Data Register (16-bit)
#define SFIOR      (*((volatile u8*)(0x50)))  // Special Function IO Register

// Bit Definitions for ADMUX Register
#define REFS1      7  // Reference Selection Bit 1
#define REFS0      6  // Reference Selection Bit 0
#define ADLAR      5  // ADC Left Adjust Result
#define MUX4       4  // Analog Channel Selection Bit 4
#define MUX3       3  // Analog Channel Selection Bit 3
#define MUX2       2  // Analog Channel Selection Bit 2
#define MUX1       1  // Analog Channel Selection Bit 1
#define MUX0       0  // Analog Channel Selection Bit 0

// Bit Definitions for ADCSRA Register
#define ADEN       7  // ADC Enable
#define ADSC       6  // ADC Start Conversion
#define ADATE      5  // ADC Auto Trigger Enable
#define ADIF       4  // ADC Interrupt Flag
#define ADIE       3  // ADC Interrupt Enable
#define ADPS2      2  // ADC Prescaler Select Bit 2
#define ADPS1      1  // ADC Prescaler Select Bit 1
#define ADPS0      0  // ADC Prescaler Select Bit 0

// Prescaler Mask
#define PRESCALER_MASK 0x07 // Mask for ADC prescaler bits (ADPS2:ADPS0)

// Channel Selection Mask
#define CHANNEL_MASK 0xE0   // Mask for clearing channel bits in ADMUX


#endif /* MCAL_ADC_ADC_PRIVATE_H_ */
