/*********************************************************/
/* Component : TIMER                                      */
/* File      : TIMER_interface.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 5 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_TIMER_TIMER_INTERFACE_H_
#define MCAL_TIMER_TIMER_INTERFACE_H_

/******************* Interfacing Macros *****************/

// TIMER0 Prescaler Options
#define TIMER0_NO_CLOCK         0
#define TIMER0_PRESCALER_1      1
#define TIMER0_PRESCALER_8      2
#define TIMER0_PRESCALER_64     3
#define TIMER0_PRESCALER_256    4
#define TIMER0_PRESCALER_1024   5

// TIMER1 Prescaler Options
#define TIMER1_NO_CLOCK         0
#define TIMER1_PRESCALER_1      1
#define TIMER1_PRESCALER_8      2
#define TIMER1_PRESCALER_64     3
#define TIMER1_PRESCALER_256    4
#define TIMER1_PRESCALER_1024   5

// TIMER1 PWM Channel Options
#define TIMER1_CHANNELA         0
#define TIMER1_CHANNELB         1

// TIMER0 Frequency Options for Fast PWM
#define TIMER0_31_KHZ   1   // Prescaler = 1
#define TIMER0_3906_HZ  2   // Prescaler = 8
#define TIMER0_488_HZ   3   // Prescaler = 32
#define TIMER0_122_HZ   4   // Prescaler = 128
#define TIMER0_30_HZ    5   // Prescaler = 1024

// Timer/Counter1 ICU Trigger Signals
#define ICU_FALLING_EDGE     0
#define ICU_RISING_EDGE      1

/******************* Function Prototypes *****************/

/* TIMER0 Functions */
void TIMER0_voidInit(void);
void TIMER0_voidStartOverFlowAsync(u8 Copy_u8Prescaler, void(*Copy_pFunction)(void));
void TIMER0_voidSTOPTIMER0(void);
void TIMER0_voidSetPreload(u8 Copy_u8PreloadValue);
void TMR0_voidStartCompareMatchAsync(u8 Copy_u8Prescaler, void(*Copy_pFunction)(void));
void TMR0_voidSetCompareMatch(u8 Copy_u8CompareMatchValue);
void TIMER0_voidFastPWM(u8 Copy_u8Freq);
void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle);

/* TIMER1 Functions */
void TIMER1_voidInit(void);
void TIMER1_voidFastNonInvertedPWM(u8 Copy_u8channel, u8 Copy_u8Prescaler);
void TIMER1_voidSetDutyCycle(u8 Copy_u8channel, u16 Coupy_u16DutyCycle);
void TIMER1_voidSetTopValue(u16 Copy_u16TopValue);
void TIMER1_voidComp(u16 Copy_u16Comp, u8 Copy_u8Channel);
void TIMER1_voidNormalMode(u8 Copy_u8Prescaler);
void TIMER1_voidRestTimer(void);
u16 Timer1_voidGetElapsedTime(void);
void TIMER1_voidStopTimer(void);
void TMR1_voidSetICUTriggerSignal(u8 Copy_u8TriggerSignal);
void TMR1_voidEnableICUInterrupt(void(*Copy_ptrToFunction)(void));
void TMR1_voidDisableICUInterrupt(void);
u16 TMR1_u16InputCaptureValue(void);




#endif /* MCAL_TIMER_TIMER_INTERFACE_H_ */
