/************************************/
/* File      : SMART_HOME_APP.c     */
/* Author    : Ahmed Hegazy        */
/* Version 	 : V2.0                 */
/************************************/
/************<include drivers from LIB layer>************/
 #include "../LIB/STD_TYPES.h"
 #include "../LIB/BIT_MATH.h"
/**********************************************/

/************<include drivers from MCAL layer>************/
 #include "../MCAL/DIO/DIO_Interface.h"
 #include "../MCAL/USART/UART_Interface.h"
/**********************************************/

/************<include drivers from HAL layer>************/

 #include "../HAL/SERVO/SERVO_Interface.h"
 #include "../HAL/LED/LED_Interface.h"
 #include "../HAL/BUZZER/BUZZER_Interface.h"
/**********************************************/


/************<include delay library>************/
 #include <util/delay.h>
/**********************************************/

/*********<include SMART HOME library>*********/
#include "SMART_HOME_Interface.h"
/**********************************************/


// Send initialization commands to the Wi-Fi module
void Wifi_voidInit()
{
	UART_voidSendStringSync("AT+CWJAP=\"ZOZ\",\"100100100\"\r\n");
	  _delay_ms(1000);                             // Wait for command to process

	  UART_voidSendStringSync("AT+CIPMUX=1\r\n");  // Enable multiple connections
	  _delay_ms(1000);                             // Wait for command to process
	  UART_voidSendStringSync("AT+CIPSERVER=1,80\r\n");  // Start server on port 80
	  _delay_ms(1000);
}




// Function to initialize the raindrop sensor and return rain status
u8 Raindrop_voidInit(void)
{
    // Read the raindrop sensor pin value and determine if it's raining
    u8 isRaining = (DIO_u8GetPinValue(PORTA, PIN4) == 0); // Active LOW signal indicates rain
    return isRaining; // Return the status as the function output
}

// Function to control the window based on rain detection
u8 checkRain(u8 isRaining)
{
    if (isRaining)
    {
        SERVO_voidRotate2(0);  // Open the window if it's raining
        return 1;               // Return 1 to indicate the window was opened
    }
    else
    {
        SERVO_voidRotate2(90);  // Close the window if it's not raining
        return 0;               // Return 0 to indicate the window was closed
    }
}


void SmokeSensor (void)
{
	if (DIO_u8GetPinValue(PORTA,PIN0)== LOW)
	{
		DIO_voidSetPinValue(PORTA,PIN7,HIGH);
		DIO_voidSetPinValue(PORTA,PIN1,HIGH);
		_delay_ms(2000);
		DIO_voidSetPinValue(PORTA,PIN7,LOW);
		DIO_voidSetPinValue(PORTA,PIN1,LOW);

	}
	else
	{
		DIO_voidSetPinValue(PORTA,PIN7,LOW);
		DIO_voidSetPinValue(PORTA,PIN1,LOW);
	}
}

