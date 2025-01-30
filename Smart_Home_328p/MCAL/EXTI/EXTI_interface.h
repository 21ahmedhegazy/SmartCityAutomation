/*********************************************************/
/* Component : EXTI                                      */
/* File      : EXTI_interface.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef MCAL_EXTI_EXTI_INTERFACE_H_
#define MCAL_EXTI_EXTI_INTERFACE_H_

// Interrupt IDs
#define EXTI_INT0 0
#define EXTI_INT1 1


// Sense Signals for INT0 and INT1
#define LOW_LEVEL    1
#define ON_CHANGE    2
#define FALLING_EDGE 3
#define RISING_EDGE  4

// Sense Signals for INT2
#define EXTI_INT2_FALLING_EDGE 0
#define EXTI_INT2_RISING_EDGE  1

// Global Interrupt Control
#define GIE_ENABLED  1
#define GIE_DISABLED 0

// Function Prototypes
void EXTI_voidInitINT0PreBuild(void);
void EXTI_voidInitINT1PreBuild(void);


void EXTI_voidEnableInterrupt(u8 Copy_u8InterruptId);
void EXTI_voidDisableInterrupt(u8 Copy_u8InterruptId);

void EXTI_voidSetSenseSignalINT0(u8 Copy_u8INT0SenseSignal);
void EXTI_voidSetSenseSignalINT1(u8 Copy_u8INT1SenseSignal);


void GIE_voidControlGlobalInterrupt(u8 Copy_u8State);

void EXTI_voidSetInt0CallBack(void (*Copy_ptrToFunction)(void));
void EXTI_voidSetInt1CallBack(void (*Copy_ptrToFunction)(void));



#endif /* MCAL_EXTI_EXTI_INTERFACE_H_ */
