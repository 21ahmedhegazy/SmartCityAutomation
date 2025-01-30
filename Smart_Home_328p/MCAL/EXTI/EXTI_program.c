/*********************************************************/
/* Component : EXTI                                      */
/* File      : EXTI_program.c                            */
/* Author    : Ahmed Hegazy                              */
/* Date      : 28.8.2023                                 */
/* Version   : V1.0                                      */
/*********************************************************/

/* Includes */
// Library Layer
#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"

// EXTI Files
#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

/* Global Pointers for Callback Functions */
void (*Global_INT0ptrToFunction)(void) = NULL_PTR;
void (*Global_INT1ptrToFunction)(void) = NULL_PTR;

/* Function Definitions */

/* Initialize INT0 with Predefined Configuration */
void EXTI_voidInitINT0PreBuild(void)
{
    // Set INT0 sense control
#if INT0_SENSE == LOW_LEVEL
    CLR_BIT(EXTI_EICRA, EICRA_ISC00);
    CLR_BIT(EXTI_EICRA, EICRA_ISC01);
#elif INT0_SENSE == ON_CHANGE
    SET_BIT(EXTI_EICRA, EICRA_ISC00);
    CLR_BIT(EXTI_EICRA, EICRA_ISC01);
#elif INT0_SENSE == FALLING_EDGE
    CLR_BIT(EXTI_EICRA, EICRA_ISC00);
    SET_BIT(EXTI_EICRA, EICRA_ISC01);
#elif INT0_SENSE == RISING_EDGE
    SET_BIT(EXTI_EICRA, EICRA_ISC00);
    SET_BIT(EXTI_EICRA, EICRA_ISC01);
#else
#error "Invalid INT0_SENSE Configuration!"
#endif

    // Set INT0 initial state
#if INT0_INITIAL_STATE == ENABLED
    SET_BIT(EXTI_EIMSK, EIMSK_INT0);
#elif INT0_INITIAL_STATE == DISABLED
    CLR_BIT(EXTI_EIMSK, EIMSK_INT0);
#else
#error "Invalid INT0_INITIAL_STATE Configuration!"
#endif
}

/* Initialize INT1 with Predefined Configuration */
void EXTI_voidInitINT1PreBuild(void)
{
    // Set INT1 sense control
#if INT1_SENSE == LOW_LEVEL
    CLR_BIT(EXTI_EICRA, EICRA_ISC10);
    CLR_BIT(EXTI_EICRA, EICRA_ISC11);
#elif INT1_SENSE == ON_CHANGE
    SET_BIT(EXTI_EICRA, EICRA_ISC10);
    CLR_BIT(EXTI_EICRA, EICRA_ISC11);
#elif INT1_SENSE == FALLING_EDGE
    CLR_BIT(EXTI_EICRA, EICRA_ISC10);
    SET_BIT(EXTI_EICRA, EICRA_ISC11);
#elif INT1_SENSE == RISING_EDGE
    SET_BIT(EXTI_EICRA, EICRA_ISC10);
    SET_BIT(EXTI_EICRA, EICRA_ISC11);
#else
#error "Invalid INT1_SENSE Configuration!"
#endif

    // Set INT1 initial state
#if INT1_INITIAL_STATE == ENABLED
    SET_BIT(EXTI_EIMSK, EIMSK_INT1);
#elif INT1_INITIAL_STATE == DISABLED
    CLR_BIT(EXTI_EIMSK, EIMSK_INT1);
#else
#error "Invalid INT1_INITIAL_STATE Configuration!"
#endif
}

/* Enable Interrupt by ID */
void EXTI_voidEnableInterrupt(u8 Copy_u8InterruptId)
{
    switch (Copy_u8InterruptId)
    {
    case 0:  // INT0
        SET_BIT(EXTI_EIMSK, EIMSK_INT0);
        break;
    case 1:  // INT1
        SET_BIT(EXTI_EIMSK, EIMSK_INT1);
        break;
    default:
        // Invalid Interrupt ID
        break;
    }
}

/* Disable Interrupt by ID */
void EXTI_voidDisableInterrupt(u8 Copy_u8InterruptId)
{
    switch (Copy_u8InterruptId)
    {
    case 0:  // INT0
        CLR_BIT(EXTI_EIMSK, EIMSK_INT0);
        break;
    case 1:  // INT1
        CLR_BIT(EXTI_EIMSK, EIMSK_INT1);
        break;
    default:
        // Invalid Interrupt ID
        break;
    }
}

/* Set Sense Signal for INT0 */
void EXTI_voidSetSenseSignalINT0(u8 Copy_u8SenseSignal)
{
    WRITE_BIT(EXTI_EICRA, EICRA_ISC00, Copy_u8SenseSignal & 0x01);
    WRITE_BIT(EXTI_EICRA, EICRA_ISC01, (Copy_u8SenseSignal >> 1) & 0x01);
}

/* Set Sense Signal for INT1 */
void EXTI_voidSetSenseSignalINT1(u8 Copy_u8SenseSignal)
{
    WRITE_BIT(EXTI_EICRA, EICRA_ISC10, Copy_u8SenseSignal & 0x01);
    WRITE_BIT(EXTI_EICRA, EICRA_ISC11, (Copy_u8SenseSignal >> 1) & 0x01);
}

/* Set Callback for INT0 */
void EXTI_voidSetInt0CallBack(void (*Copy_ptrToFunction)(void))
{
    if (Copy_ptrToFunction != NULL_PTR)
    {
        Global_INT0ptrToFunction = Copy_ptrToFunction;
    }
}

/* Set Callback for INT1 */
void EXTI_voidSetInt1CallBack(void (*Copy_ptrToFunction)(void))
{
    if (Copy_ptrToFunction != NULL_PTR)
    {
        Global_INT1ptrToFunction = Copy_ptrToFunction;
    }
}

/* Control Global Interrupts */
void GIE_voidControlGlobalInterrupt(u8 Copy_u8State)
{
    WRITE_BIT(GIE_SREG, SREG_I, Copy_u8State);
}

/* ISR for INT0 */
void __vector_1(void) __attribute__((signal));
void __vector_1(void)
{
    if (Global_INT0ptrToFunction)
    {
        Global_INT0ptrToFunction();
    }
}

/* ISR for INT1 */
void __vector_2(void) __attribute__((signal));
void __vector_2(void)
{
    if (Global_INT1ptrToFunction)
    {
        Global_INT1ptrToFunction();
    }
}
