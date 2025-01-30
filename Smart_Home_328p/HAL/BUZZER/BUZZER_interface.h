/*********************************************************/
/* Component : BUZZER                                      */
/* File      : BUZZER_interface.h                            */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 12 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/


#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_

// Function to initialize the buzzer pin
void BUZZER_voidInt(u8 Copy_u8PortID , u8 Copy_u8PinID);

// Function to turn on the buzzer
void BUZZER_voidTurnOn(u8 Copy_u8PortID , u8 Copy_u8PinID);

// Function to turn off the buzzer
void BUZZER_voidTurnOff(u8 Copy_u8PortID , u8 Copy_u8PinID);

// Function to toggle the buzzer
void BUZZER_voidToggle(u8 Copy_u8PortID , u8 Copy_u8PinID);

#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
