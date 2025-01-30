/************************************/
/* File      : SERVO_Interface.h    */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V1.0                 */
/************************************/
#ifndef HAL_SERVO_SERVO_INTERFACE_H_
#define HAL_SERVO_SERVO_INTERFACE_H_

#define CHANNELA  0
#define CHANNELB  1


void SERVO_voidInit(void);

void SERVO_voidRotate1(u8 Copy_u8Angle);
void SERVO_voidRotate2(u8 Copy_u8Angle);
void SERVO_voidRotate3(u8 Copy_u8Angle);
void SERVO_voidRotate4(u8 Copy_u8Angle);





#endif /* HAL_SERVO_SERVO_INTERFACE_H_ */



