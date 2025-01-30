/*********************************************************/
/* Component : TIMER                                      */
/* File      : TIMER_program.c                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 5 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
/* Includes */
// Library Layer
#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"

// Timer Files
#include "TIMER_interface.h"
#include "TIMER_config.h"
#include "TIMER_private.h"

// Global pointers for callback functions
void (*Global_pFun_TIMER0OverFlow)(void) = NULL_PTR;
void (*Global_pfun_TMR0ComMatch)(void) = NULL_PTR;
void (*Copy_GlobalptrToFunction)(void) = NULL_PTR;

/* Timer0 Initialization Function */
void TIMER0_voidInit(void)
{
    // Set the mode of TIMER0
#if TIMER0_MODE == NORMAL_MODE
    CLR_BIT(TIMER0_TCCR0, TCCR0_WGM0);
    CLR_BIT(TIMER0_TCCR0, TCCR0_WGM1);

#elif TIMER0_MODE == CTC_MODE
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM0);
    CLR_BIT(TIMER0_TCCR0, TCCR0_WGM1);

#elif TIMER0_MODE == FAST_PWM
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM0);
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM1);

#elif TIMER0_MODE == PHASE_CORRECT_PWM
    CLR_BIT(TIMER0_TCCR0, TCCR0_WGM0);
    SET_BIT(TIMER0_TCCR0, TCCR0_WGM1);

#else
#error "Invalid TIMER0 mode configuration"
#endif
    // Additional corrections: Clear and configure COM bits
        CLR_BIT(TIMER0_TCCR0, TCCR0_COM0);
        CLR_BIT(TIMER0_TCCR0, TCCR0_COM1);
}

/* Start Timer0 in Overflow Mode Asynchronously */
void TIMER0_voidStartOverFlowAsync(u8 Copy_u8Prescaler, void(*Copy_pFunction)(void))
{
    // Enable overflow interrupt
    SET_BIT(TIMSK, TIMSK_TOIE0);

    // Set callback function for overflow interrupt
    Global_pFun_TIMER0OverFlow = Copy_pFunction;

    // Set prescaler
    TIMER0_TCCR0 &= PRESCALER_MASK;  // Mask the prescaler bits
    TIMER0_TCCR0 |= Copy_u8Prescaler; // Apply the desired prescaler
}

/* Stop Timer0 */
void TIMER0_voidSTOPTIMER0(void)
{
    TIMER0_TCCR0 &= PRESCALER_MASK; // Clear prescaler bits
}

/* Set Preload Value for Timer0 */
void TIMER0_voidSetPreload(u8 Copy_u8PreloadValue)
{
    TIMER0_TCNT0 = Copy_u8PreloadValue;
}

/* Start Timer0 in Compare Match Mode Asynchronously */
void TMR0_voidStartCompareMatchAsync(u8 Copy_u8Prescaler, void(*Copy_pFunction)(void))
{
    // Enable compare match interrupt
    SET_BIT(TIMSK, TIMSK_OCIE0);

    // Set callback function for compare match interrupt
    Global_pfun_TMR0ComMatch = Copy_pFunction;

    // Set prescaler
    TIMER0_TCCR0 &= PRESCALER_MASK;  // Mask the prescaler bits
    TIMER0_TCCR0 |= Copy_u8Prescaler; // Apply the desired prescaler
}

/* Set Compare Match Value for Timer0 */
void TMR0_voidSetCompareMatch(u8 Copy_u8CompareMatchValue)
{
    TIMER0_OCR0 = Copy_u8CompareMatchValue;
}

/* Set Fast PWM on Timer0 with Specific Frequency */
//void TIMER0_voidFastPWM(u8 Copy_u8Freq)
//{
//    // Set non-inverted PWM mode
//    SET_BIT(TIMER0_TCCR0, TCCR0_COM1); // Bit 5
//    CLR_BIT(TIMER0_TCCR0, TCCR0_COM0); // Bit 4
//
//    // Set prescaler
//    TIMER0_TCCR0 &= PRESCALER_MASK;  // Mask the prescaler bits
//    TIMER0_TCCR0 |= Copy_u8Freq;  // Apply the desired frequency (prescaler)
//}

/* Set Duty Cycle for Fast PWM on Timer0 */
void TIMER0_voidSetDutyCycle(u8 Copy_u8DutyCycle)
{
    TIMER0_OCR0 = ((u16)(Copy_u8DutyCycle * 255)) / 100;
}

/* Timer1 Initialization Function */
void TIMER1_voidInit(void)
{
    // Configure Timer1 for fast PWM with Mode 14
    SET_BIT(TIMER1_TCCR1A, 1); // Non-inverted mode
    CLR_BIT(TIMER1_TCCR1A, 0);
    SET_BIT(TIMER1_TCCR1B, 3); // WGM Mode 14
    SET_BIT(TIMER1_TCCR1B, 4); // WGM Mode 14
}

/* Start Fast Non-Inverted PWM on Timer1 */
void TIMER1_voidFastNonInvertedPWM(u8 Copy_u8channel, u8 Copy_u8Prescaler)
{
    switch (Copy_u8channel)
    {
    case TIMER1_CHANNELA:
        SET_BIT(TIMER1_TCCR1A, TCCRA_COM1A1);
        CLR_BIT(TIMER1_TCCR1A, TCCRA_COM1A0);
        break;
    case TIMER1_CHANNELB:
        SET_BIT(TIMER1_TCCR1A, TCCRA_COM1B1);
        CLR_BIT(TIMER1_TCCR1A, TCCRA_COM1B0);
        break;

    }

    // Set prescaler for Timer1
    TIMER1_TCCR1B &= PRESCALER_MASK;  // Mask the prescaler bits
    TIMER1_TCCR1B |= Copy_u8Prescaler; // Apply the desired prescaler
}

/* Set Duty Cycle for Timer1 PWM */
void TIMER1_voidSetDutyCycle(u8 Copy_u8channel, u16 Coupy_u16DutyCycle)
{
    switch (Copy_u8channel)
    {
    case TIMER1_CHANNELA:
        TIMER1_OCR1A = Coupy_u16DutyCycle;
        break;
    case TIMER1_CHANNELB:
        TIMER1_OCR1B = Coupy_u16DutyCycle;
        break;
    }
}

/* Set Top Value for PWM in Mode 14 on Timer1 */
void TIMER1_voidSetTopValue(u16 Copy_u16TopValue)
{
    TIMER1_ICR1 = Copy_u16TopValue;
}

///* Run Timer1 in Normal Mode */
//void TIMER1_voidNormalMode(u8 Copy_u8Prescaler)
//{
//    TIMER1_TCCR1B &= PRESCALER_MASK;  // Mask the prescaler bits
//    TIMER1_TCCR1B |= Copy_u8Prescaler; // Apply the desired prescaler
//}

///* Reset Timer1 */
//void TIMER1_voidRestTimer(void)
//{
//    TIMER1_ICR1 = 0;
//}

///* Get Elapsed Time for Timer1 */
//u16 Timer1_voidGetElapsedTime(void)
//{
//    return TIMER1_ICR1;
//}

/* Stop Timer1 */
void TIMER1_voidStopTimer(void)
{
    TIMER1_TCCR1B &= PRESCALER_MASK;  // Clear prescaler bits to stop the timer

}

///* Set Trigger Signal for ICU on Timer1 */
//void TMR1_voidSetICUTriggerSignal(u8 Copy_u8TriggerSignal)
//{
//    switch (Copy_u8TriggerSignal)
//    {
//    case ICU_FALLING_EDGE:
//        CLR_BIT(TIMER1_TCCR1B, 6);
//        break;
//
//    case ICU_RISING_EDGE:
//        SET_BIT(TIMER1_TCCR1B, 6);
//        break;
//    }
//}
//
///* Enable ICU Interrupt on Timer1 */
//void TMR1_voidEnableICUInterrupt(void (*Copy_ptrToFunction)(void))
//{
//    Copy_GlobalptrToFunction = Copy_ptrToFunction;
//    SET_BIT(TIMSK, 5); // Enable ICU interrupt
//}
//
///* Disable ICU Interrupt on Timer1 */
//void TMR1_voidDisableICUInterrupt(void)
//{
//    CLR_BIT(TIMSK, 5); // Disable ICU interrupt
//}
//
///* Get Input Capture Value from Timer1 */
//u16 TMR1_u16InputCaptureValue(void)
//{
//    return TIMER1_ICR1;
//}
//
///* Timer1 Input Capture Interrupt Service Routine */
//void __vector_6(void) __attribute__((signal));
//void __vector_6(void)
//{
//    if (Copy_GlobalptrToFunction != NULL_PTR)
//    {
//        Copy_GlobalptrToFunction();
//    }
//}

/* Timer0 Overflow Interrupt Service Routine */
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
    if (Global_pFun_TIMER0OverFlow != NULL_PTR)
    {
        Global_pFun_TIMER0OverFlow();
    }
}

/* Timer0 Compare Match Interrupt Service Routine */
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
    if (Global_pfun_TMR0ComMatch != NULL_PTR)
    {
        Global_pfun_TMR0ComMatch();
    }
}
