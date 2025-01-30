/*
 * Motor_Interface.h
 *
 *  Created on: Aug 26, 2023
 *      Author: Hegazy
 */

#ifndef HAL_DC_MOTOR_MOTOR_INTERFACE_H_
#define HAL_DC_MOTOR_MOTOR_INTERFACE_H_


void DCMotor_voidInit(u8 Copy_u8PortID ,u8 Copy_u8PinID);
void DCMotor_voidMotorON(u8 Copy_u8PortID ,u8 Copy_u8PinID);
void DCMotor_voidMotorOFF(u8 Copy_u8PortID ,u8 Copy_u8PinID);

void DCMotor_voidInitPB(void);
void DCMotor_voidRotateCW(void);
void DCMotor_voidRotateACW(void);
void DCMotor_voidStopMotor(void);

#endif /* HAL_DC_MOTOR_MOTOR_INTERFACE_H_ */
