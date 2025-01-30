/************************************/
/* File      : DIO_Interface.h      */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V1.0                 */
/************************************/

#ifndef  MCAL_DIO_DIO_INTERFACE_H_
#define  MCAL_DIO_DIO_INTERFACE_H_
/*********************************************************************************************************************/
/************************************************ Interfacing macros *************************************************/
/*********************************************************************************************************************/

#define PIN0      0
#define PIN1      1
#define PIN2      2
#define PIN3      3
#define PIN4      4
#define PIN5      5
#define PIN6      6
#define PIN7      7

#define PORTA     0
#define PORTB     1
#define PORTC     2
#define PORTD     3

#define INPUT           0
#define OUTPUT          1
#define INPUT_PULL_UP   2

#define HIGH    1
#define LOW     0

#define PORT_OUTPUT		0xFF
#define PORT_INPUT		0

#define PORT_HIGH		0xFF
#define PORT_LOW		0

/*********************************************************************************************************************/
/********************************************* Function's prototypes *************************************************/
/*********************************************************************************************************************/
                                                  /*PORT*/

void DIO_voidSetPortDirection  (u8 Copy_u8PORT , u8 Copy_u8DIRECTION);                        /* Set port direction */
void DIO_voidSetPortValue      (u8 Copy_u8PORT , u8 Copy_u8VALUE);                            /* Set port value     */
void DIO_voidClearPortValue    (u8 Copy_u8PORT );                                             /* Clear port value   */
void DIO_voidTogglePortValue   (u8 Copy_u8PORT );                                             /* Toggle all port    */
u8   DIO_u8GetPortValue        (u8 Copy_u8PORT );                                             /* Get port value     */

											      /*PIN*/

void DIO_voidSetPinDirection   (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8DIRECTION);        /* Set pin direction  */
void DIO_voidSetPinValue       (u8 Copy_u8PORT , u8 Copy_u8PIN , u8 Copy_u8VALUE);            /* Set pin value      */
void DIO_voidClearPinValue     (u8 Copy_u8PORT , u8 Copy_u8PIN);                              /* Clear pin value    */
void DIO_voidTogglePinValue    (u8 Copy_u8PORT , u8 Copy_u8PIN);							  /* Toggle pin         */
u8   DIO_u8GetPinValue         (u8 Copy_u8PORT , u8 Copy_u8PIN );                             /* Get pin value      */

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
#endif
