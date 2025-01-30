/*********************************************************/
/* Component : SERVO                                     */
/* File      : SERVO_config.h                            */
/* Author    : Ahmed Hegazy                                     */
/* Date      : 11 . 9 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef HAL_SERVO_SERVO_CONFIG_H_
#define HAL_SERVO_SERVO_CONFIG_H_

// Timer1 prescaler options
#define TIMER1_NO_CLOCK      0
#define TIMER1_PRESCALER_1   1
#define TIMER1_PRESCALER_8   2
#define TIMER1_PRESCALER_64  3
#define TIMER1_PRESCALER_256 4
#define TIMER1_PRESCALER_1024 5

// Timer1 channel selection for servo motor
#define CHANNEL CHANNELB  // Use CHANNELA for Timer1 Channel A

#define TIMER_CHANNEL     CHANNELB
#define SERVO_PORT        DIO_PORTB
#define SERVO_PIN         DIO_PIN2

#endif /* HAL_SERVO_SERVO_CONFIG_H_ */
