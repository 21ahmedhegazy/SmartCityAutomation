/*
 * SERVO_Interface.h
 *
 *  Created on: Sep 11, 2023
 *      Author: Hegazy
 */

#ifndef HAL_SERVO_SERVO_INTERFACE_H_
#define HAL_SERVO_SERVO_INTERFACE_H_

#define CHANNELA  0
#define CHANNELB  1


void SERVO_voidInit(void);

void SERVO_voidRotate(u8 Copy_u8Angle);

#endif /* HAL_SERVO_SERVO_INTERFACE_H_ */


//void SERVO_voidInit(u8 Copy_u8PortID ,u8 Copy_u8PinID , u8 Copy_u8CHANNAL);
