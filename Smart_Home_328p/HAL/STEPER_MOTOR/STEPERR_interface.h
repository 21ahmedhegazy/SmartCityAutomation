/*********************************************************/
/* Component : STEPPER_MOTOR                                     */
/* File      : STM_interface.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef HAL_STEPER_MOTOR_STEPERR_INTERFACE_H_
#define HAL_STEPER_MOTOR_STEPERR_INTERFACE_H_

// Function declarations for stepper motor control
void STEPPER_voidInit(void);
void Stepper_voidRotateCW(void);
void Stepper_voidRotateACW(void);
void Stepper_voidHalfSetpRotateCW(void);
void Stepper_voidHalfSetpRotateACW(void);

#endif /* HAL_STEPER_MOTOR_STEPERR_INTERFACE_H_ */
