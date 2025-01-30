/*
 * STEPPER_Interface.h
 *
 *  Created on: Aug 23, 2023
 *      Author: Hegazy
 */

#ifndef HAL_STEPPER_STEPPER_INTERFACE_H_
#define HAL_STEPPER_STEPPER_INTERFACE_H_

void STEPPER_voidInit(void);
//full step
void Stepper_voidRotateCW(void);
void Stepper_voidRotateACW(void);

//half step
void Stepper_voidHalfSetpRotateCW(void);
void Stepper_voidHalfSetpRotateACW(void);


#endif /* HAL_STEPPER_STEPPER_INTERFACE_H_ */
