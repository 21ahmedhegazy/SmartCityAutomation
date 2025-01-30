/*********************************************************/
/* Component : EXTI                                      */
/* File      : EXTI_private.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_

// Registers and Bits for ATmega328P
#define EXTI_EICRA     (*((volatile u8 *)(0x69)))
#define EICRA_ISC00    0
#define EICRA_ISC01    1
#define EICRA_ISC10    2
#define EICRA_ISC11    3


#define EXTI_MCUSR     (*((volatile u8 *)(0x54)))
#define MCUSR_ISC2     6

#define EXTI_EIMSK     (*((volatile u8 *)(0x3D)))
#define EIMSK_INT0     0
#define EIMSK_INT1     1


#define GIE_SREG       (*((volatile u8 *)(0x5F)))
#define SREG_I         7

#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
