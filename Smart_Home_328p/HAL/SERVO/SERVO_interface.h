/*********************************************************/
/* Component : SERVO                                     */
/* File      : SERVO_interface.h                            */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 11 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef HAL_SERVO_SERVO_INTERFACE_H_
#define HAL_SERVO_SERVO_INTERFACE_H_

// Channel options in Timer1 for PWM or CTC
#define TIMER1_CHANNELA  0
#define TIMER1_CHANNELB  1

// Function declarations
void SERVO_Int(void);
void SERVO_Rotate(u8 CopyAngle);

void DOOR_voidDoorOpen(void);
void DOOR_voidDoorClose(void);

#endif /* HAL_SERVO_SERVO_INTERFACE_H_ */
