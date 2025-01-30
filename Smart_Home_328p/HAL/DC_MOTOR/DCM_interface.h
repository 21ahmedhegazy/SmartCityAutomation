/*********************************************************/
/* Component : DCM                                     */
/* File      : DCM_interface.h                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/
#ifndef HAL_DC_MOTOR_DCM_INTERFACE_H_
#define HAL_DC_MOTOR_DCM_INTERFACE_H_

// Define the port used for the DC Motor (same as in config.h)
#define DCM_PORT DIO_PORTB

// Function to initialize the DC motor
void DCM_voidInit(void);

// Function to move the motor forward
void DCM_voidMotorForward(u8 Copy_u8_PortID, u8 Copy_u8_PinID1);

// Function to move the motor backward
void DCM_voidMotorBackward(u8 Copy_u8_PortID, u8 Copy_u8_PinID1, u8 Copy_u8_PinID2);

// Function to stop the motor
void DCM_voidMotorStop(u8 Copy_u8_PortID, u8 Copy_u8_PinID1);

#endif /* HAL_DC_MOTOR_DCM_INTERFACE_H_ */
