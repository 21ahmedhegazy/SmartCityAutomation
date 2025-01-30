/************************************/
/* Component : LED                */
/* File      : LED_Interface.h      */
/* Author    :Ahmed Hegazy           */
/* Date 	 : 21/7/2023            */
/* Version 	 : V1.0                 */
/************************************/

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

#define VCC     255
#define GROUND  0

// Function declarations for LED control
void LED_voidLedIni(u8 Copy_u8PortID , u8 Copy_u8PinID);
void LED_voidLPortIni(u8 Copy_u8PortID);
void LED_voidSetLedOn(u8 Copy_u8PortID , u8 Copy_u8PinID);
void LED_voidSetLedOff(u8 Copy_u8PortID , u8 Copy_u8PinID);
void LED_voidSetToggleLed(u8 Copy_u8PortID , u8 Copy_u8PinID);
void LED_voidSetPortLedOn(u8 Copy_u8PortID);
void LED_voidSetPortLedOff(u8 Copy_u8PortID);

#endif /* HAL_LED_LED_INTERFACE_H_ */
