/*********************************************************/
/* File      : EXTI_private.h                            */
/* Author    : Ahmed Hegazy                              */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef MCAL_EXTI_EXTI_PRIVATE_H_
#define MCAL_EXTI_EXTI_PRIVATE_H_


/*********************Registers' Addresses*******************/
#define EXTI_MCUCR     (*((volatile u8 * )(0x55)))
#define MCUCR_ISC01    1   //Interrupt Sense Control 0 , 1
#define MCUCR_ISC00    0
#define MCUCR_ISC11    3
#define MCUCR_ISC10    2



#define EXTI_MCUCSR    (*((volatile u8 * )(0x54)))
#define MCUCSR_ISC2    6


#define EXTI_GIFR      (*((volatile u8 * )(0x5A)))


#define EXTI_GICR      (*((volatile u8 * )(0x5B)))
#define GICR_INT0      6
#define GICR_INT1      7
#define GICR_INT2      5


#define GIE_SREG       (*((volatile u8 * )(0x5F)))
#define SREG_I         7


#endif /* MCAL_EXTI_EXTI_PRIVATE_H_ */
