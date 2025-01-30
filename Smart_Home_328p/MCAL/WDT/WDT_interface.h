/*********************************************************/
/* Component : WDT                                      */
/* File      : WDT_interface.h                             */
/* Author    : Ahmed Hegazy                                         */
/* Date      : 16 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef MCAL_WDT_WDT_INTERFACE_H_
#define MCAL_WDT_WDT_INTERFACE_H_

// Function to enable the Watchdog Timer
void WDT_voidEnable(void);

// Function to set the sleep interval for the Watchdog Timer
void WDT_voidSleep(u8 Copy_u8SleepInterval);

// Function to disable the Watchdog Timer
void WDT_voidDisable(void);

#endif /* MCAL_WDT_WDT_INTERFACE_H_ */
