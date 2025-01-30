/*********************************************************/
/* Component : WDT                                       */
/* File      : WDT_private.h                             */
/* Author    : Ahmed Hegazy                              */
/* Date      : 16.9.2023                                 */
/* Version   : V1.1                                      */
/*********************************************************/

#ifndef MCAL_WDT_WDT_PRIVATE_H_
#define MCAL_WDT_WDT_PRIVATE_H_

#define MCUSR       *((volatile u8 *)(0x54))
#define MCUSR_PORF  0  // Power-on Reset Flag
#define MCUSR_EXTRF 1  // External Reset Flag
#define MCUSR_BORF  2  // Brown-out Reset Flag
#define MCUSR_WDRF  3  // Watchdog Reset Flag

// Watchdog Timer Control Register
#define WDTCSR      *((volatile u8 *)(0x60))

// WDT control bits
#define WDTCSR_WDIF 7  // Watchdog Interrupt Flag
#define WDTCSR_WDIE 6  // Watchdog Interrupt Enable
#define WDTCSR_WDCE 4  // Watchdog Change Enable
#define WDTCSR_WDE  3  // Watchdog Enable
#define WDTCSR_WDP3 5  // Prescaler bit 3
#define WDTCSR_WDP2 2  // Prescaler bit 2
#define WDTCSR_WDP1 1  // Prescaler bit 1
#define WDTCSR_WDP0 0  // Prescaler bit 0

#endif /* MCAL_WDT_WDT_PRIVATE_H_ */
