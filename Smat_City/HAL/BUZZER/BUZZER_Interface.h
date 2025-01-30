/************************************/
/* File      : BUZZER_Interface.h   */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V1.0                 */
/************************************/
#ifndef HAL_BUZZER_BUZZER_INTERFACE_H_
#define HAL_BUZZER_BUZZER_INTERFACE_H_


void BUZZER_voidInit(u8 Copy_u8PortID ,u8 Copy_u8PinID);
void BUZZER_voidBuzzerON(u8 Copy_u8PortID ,u8 Copy_u8PinID);
void BUZZER_voidBuzzerOFF(u8 Copy_u8PortID ,u8 Copy_u8PinID);
void BUZZER_voidBuzzerToggel(u8 Copy_u8PortID ,u8 Copy_u8PinID);


#endif /* HAL_BUZZER_BUZZER_INTERFACE_H_ */
