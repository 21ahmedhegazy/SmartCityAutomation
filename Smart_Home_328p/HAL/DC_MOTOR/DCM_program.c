/*********************************************************/
/* Component : DCM                                     */
/* File      : DCM_program.c                             */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#include "../../LIB/Bit_Maths.h"
#include "../../LIB/STD_TYPES.h"

// Include DIO functions for controlling pins
#include "../../MCAL/DIO/DIO_interface.h"

// Include DC Motor interface and configuration files
#include "DCM_interface.h"
#include "DCM_private.h"
#include "DCM_config.h"

// Function to initialize the DC motor
void DCM_voidInit(void)
{
    // Set the entire port for the motor as output (using the configured port DCM_PORT)
    DIO_voidSetPortDirection(DCM_PORT, DIO_PORT_OUTPUT);
}

// Function to move the motor forward (set one pin high, the other low)
void DCM_voidMotorForward(u8 Copy_u8_PortID, u8 Copy_u8_PinID1)
{
    // Set the first pin high to move the motor forward
    DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID1, DIO_HIGH_OUTPUT);
    // Optionally, if using a second pin for backward movement, it would be set to LOW
    // DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID2, DIO_LOW_OUTPUT);
}

// Function to move the motor backward (set one pin low, the other high)
void DCM_voidMotorBackward(u8 Copy_u8_PortID, u8 Copy_u8_PinID1, u8 Copy_u8_PinID2)
{
    // Set the first pin low and the second pin high to move the motor backward
    DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID1, DIO_LOW_OUTPUT);
    DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID2, DIO_HIGH_OUTPUT);
}

// Function to stop the motor (set both pins low)
void DCM_voidMotorStop(u8 Copy_u8_PortID, u8 Copy_u8_PinID1)
{
    // Set the motor pins to low to stop the motor
    DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID1, DIO_LOW_OUTPUT);
    // DIO_voidSetPinValue(Copy_u8_PortID, Copy_u8_PinID2, DIO_LOW_OUTPUT);
}
