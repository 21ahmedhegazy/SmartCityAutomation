/*********************************************************/
/* Component : STEPPER_MOTOR                                     */
/* File      : STM_config.h                             */
/* Author    : Ahmed Hegazy                                      */
/* Date      : 28 . 8 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef HAL_STEPER_MOTOR_STEPERR_CONFIG_H_
#define HAL_STEPER_MOTOR_STEPERR_CONFIG_H_

// Define the port and pins for the stepper motor control
#define STEPPER_PORT DIO_PORTD  // Change this to DIO_PORTB or DIO_PORTC if needed
#define Coil_Blue    DIO_PIN0
#define Coil_Pink    DIO_PIN1
#define Coil_Yellow  DIO_PIN2
#define Coil_Orange  DIO_PIN3

#endif /* HAL_STEPER_MOTOR_STEPERR_CONFIG_H_ */
