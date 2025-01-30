/*********************************************************/
/* Component : KPD                                       */
/* File      : KPD_config.h                              */
/* Author    : Hegazy                                     */
/* Date      : 28 . 7 . 2023                             */
/* Version   : V1.0                                      */
/*********************************************************/

#ifndef HAL_KPD_KPD_CONFIG_H_
#define HAL_KPD_KPD_CONFIG_H_

#define VALUES {{'1' , '2' , '3' , '4'},{'5' , '6' , '7' , '8'},{'9' , 'A' , 'B' , 'C'},{'D' , 'E' , 'F' , 'P'}};

//macro for the state of no keys are pressed
#define NO_PRESSED_KEY  '0'

//Available options : DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
#define KPD_PORT   PORTB

//Available options : DIO_PIN0->DIO_PIN7
#define ROW0_PIN  PIN0
#define ROW1_PIN  PIN1
#define ROW2_PIN  PIN2
#define ROW3_PIN  PIN3

#define COL0_PIN  PIN4
#define COL1_PIN  PIN5
#define COL2_PIN  PIN6
#define COL3_PIN  PIN7

#endif /* HAL_KPD_KPD_CONFIG_H_ */
