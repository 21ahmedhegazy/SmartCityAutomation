/************************************/
/* File      : LED_Interface.h      */
/* Author    : Ahmed Hegazy          */
/* Version 	 : V1.0                 */
/************************************/

#ifndef HAL_LED_LED_INTERFACE_H_
#define HAL_LED_LED_INTERFACE_H_

#define VCC  1
#define GROUND 0

void LED_voidLedInit         (u8 Copy_u8PORT , u8 Copy_u8PIN);
void LED_voidPortLedInit     (u8 Copy_u8PORT );

void LED_voidLedOn (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Type);
void LED_voidLedZOff    		 (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8Type);

void LED_voidPortLedOn 		 (u8 Copy_u8PORT ,  u8 Copy_u8Type);
void LED_voidPortLedOff 	 (u8 Copy_u8PORT ,  u8 Copy_u8Type);

void LED_voidLedToggle       (u8 Copy_u8PORT , u8 Copy_u8PIN  );
void LED_voidPortLedToggle 	 (u8 Copy_u8PORT );
#endif /* HAL_LED_LED_INTERFACE_H_ */
