/*********************************************************/
/* File      : EXTI_interface.h                          */
/* Author    : Ahmed Hegazy                              */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_


/***********************************************************************/
/*************************Interfacing macros****************************/
/***********************************************************************/

//Interrupt IDs
#define EXTI_INT0     0
#define EXTI_INT1     1
#define EXTI_INT2     2

//Sense signals for INT0
#define EXTI_INT0_FALLING_EDGE   0
#define EXTI_INT0_RISING_EDGE    1
#define EXTI_INT0_ON_CHANGE      2
#define EXTI_INT0_LOW_LEVEL      3


//Sense signals for INT1
#define EXTI_INT1_FALLING_EDGE   0
#define EXTI_INT1_RISING_EDGE    1
#define EXTI_INT1_ON_CHANGE      2
#define EXTI_INT1_LOW_LEVEL      3


//Sense signals for INT2
#define EXTI_INT2_FALLING_EDGE   0
#define EXTI_INT2_RISING_EDGE    1

//State of Global Interrupt
#define GIE_ENABLED              1
#define GIE_DISABLED             0

/***********************************************************************/
/************************Functions' prototypes**************************/
/***********************************************************************/


/*Description : This function shall set the direction of any pin -> [output , input] */
/*Input       : portID , pinId , direction                                           */
/*Return      : void                                                                 */
void EXTI_voidEnableInterrupt(u8 Copy_u8InterruptId);


void EXTI_voidDisableInterrupt(u8 Copy_u8InterruptId);


void EXTI_voidSetSenseSignalINT0(u8 Copy_u8INT0SenseSignal);


void EXTI_voidSetSenseSignalINT1(u8 Copy_u8INT1SenseSignal);


void EXTI_voidSetSenseSignalINT2(u8 Copy_u8INT2SenseSignal);

void EXTI_voidControlGlobalInterrupt(u8 Copy_u8State);

void EXTI_voidSetCallbackINT0(void (*Copy_voidFuncptr) (void));


#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
