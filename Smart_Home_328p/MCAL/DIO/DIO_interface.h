/*********************************************************/
/* Component : DIO                                       */
/* File      : DIO_interface.h                           */
/* Author    : Ahmed Hegazy                              */
/* Date      : 25 . 4 . 2024                             */
/* Version   : V1.0                                      */
/*********************************************************/


/*preprocessor header file guard*/
#ifndef MCAL_DIO_DIO_INTERFACE_H_
#define MCAL_DIO_DIO_INTERFACE_H_

/***********************************************************************/
/*************************Interfacing macros****************************/
/***********************************************************************/

#define DIO_PORTB               1
#define DIO_PORTC               2
#define DIO_PORTD               3

// Macros for pin ID
#define DIO_PIN0                0
#define DIO_PIN1                1
#define DIO_PIN2                2
#define DIO_PIN3                3
#define DIO_PIN4                4
#define DIO_PIN5                5
#define DIO_PIN6                6
#define DIO_PIN7                7

// Macros for pin direction
#define DIO_PIN_OUTPUT          1
#define DIO_PIN_INPUT_FLOAT     0
#define DIO_PIN_INPUT_PULL_UP   2

// Macros for pin value
#define DIO_HIGH_OUTPUT         1
#define DIO_LOW_OUTPUT          0

#define DIO_PORT_OUTPUT         255
#define DIO_PORT_INPUT          0

#define DIO_PORT_HIGH           255
#define DIO_PORT_LOW            0


/***********************************************************************/
/************************Functions' prototypes**************************/
/***********************************************************************/


/*Description : This function shall set the direction of any pin -> [output , input] */
/*Input       : portID , pinId , direction                                           */
/*Return      : void                                                                 */
void DIO_voidSetPinDirection(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinDirection);

void DIO_voidSetPortDirection(u8 Copy_u8PortID , u8 Copy_u8PortDirection);

/*Description : This function shall set the value of any pin -> [high , low]         */
/*Input       : portID , pinId , value                                               */
/*Return      : void                                                                 */
void DIO_voidSetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID , u8 Copy_u8PinValue);


/*Description : This function shall get the value of any input pin                   */
/*Input       : portID , pinId                                                       */
/*Return      : u8 : pin value                                                       */
u8 DIO_u8GetPinValue(u8 Copy_u8PortID , u8 Copy_u8PinID);


void DIO_voidTogglePin(u8 Copy_u8PortID ,u8 Copy_u8PinID);

void DIO_voidPortValue(u8 Copy_u8PortID,u8 Copy_u8PortValue);




#endif /* MCAL_DIO_DIO_INTERFACE_H_ */
