/*********************************************************/
/* Component : WDT                                       */
/* File      : WDT_program.c                             */
/* Author    : Ahmed Hegazy                              */
/* Date      : 16.9.2023                                 */
/* Version   : V1.1                                      */
/*********************************************************/

#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"
#include "WDT_config.h"
#include "WDT_interface.h"
#include "WDT_private.h"

// Enable the Watchdog Timer
void WDT_voidEnable(void)
{
    // Enable WDT with default timeout
    SET_BIT(WDTCSR, WDTCSR_WDE);
}

// Set the sleep interval for the Watchdog Timer
void WDT_voidSleep(u8 Copy_u8SleepInterval)
{
    // Timed sequence to modify prescaler bits and WDE
    WDTCSR |= (1 << WDTCSR_WDCE) | (1 << WDTCSR_WDE);  // Enable change sequence

    // Clear existing prescaler bits and set new interval
    WDTCSR = (Copy_u8SleepInterval & 0b111) | (1 << WDTCSR_WDE);
}

// Disable the Watchdog Timer
void WDT_voidDisable(void)
{
    // Timed sequence to disable WDT
    WDTCSR |= (1 << WDTCSR_WDCE) | (1 << WDTCSR_WDE);  // Enable change sequence
    WDTCSR = 0x00;  // Disable WDT
}
