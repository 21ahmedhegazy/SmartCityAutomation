/************************************/
/* File      : main.c               */
/* Author    : Ahmed Hegazy         */
/* Version 	 : V3.0                 */
/************************************/

/************<include drivers from LIB layer>************/
#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
/**********************************************/

/************<include drivers from MCAL layer>************/
#include "MCAL/DIO/DIO_Interface.h"
#include "MCAL/USART/UART_Interface.h"
/**********************************************/

/************<include drivers from HAL layer>************/
#include "HAL/SERVO/SERVO_Interface.h"
#include "HAL/LED/LED_Interface.h"
#include "HAL/BUZZER/BUZZER_Interface.h"
/**********************************************/

/************<include delay library>************/
#include <util/delay.h>
/**********************************************/

/*********<include SMART HOME library>*********/
#include "APP/SMART_HOME_Interface.h"
/**********************************************/
u8 Local_u8ReceivedBuffer[150];  // Buffer to hold incoming data
u8 Local_u8Index = 0;            // Index for the buffer
u8 Local_u8Command = 0;          // Variable to store extracted command from GET request

// Function prototype to check if UART data is available
u8 UART_u8IsDataAvailable(void);

void main(void) {
	/*** Initialize Peripherals ***/
    LED_voidLedInit(PORTA, PIN7);    // Initialize LED 0
    LED_voidLedInit(PORTA, PIN1);    // Initialize LED 1
    LED_voidLedInit(PORTA, PIN2);    // Initialize LED 2
//    LED_voidLedInit(PORTA, PIN3);  // Initialize LED for raindrop sensor
    SERVO_voidInit();                // Initialize Servo Motor
    UART_voidInit();                 // Initialize UART for communication

    Wifi_voidInit();			     // Initialize WiFi module

    /*** Main Program Loop ***/
    while (1) {
    	SmokeSensor(); // Check smoke levels and take action if necessary

    	    /*** Rain Detection Process ***/
    	        u8 isRaining = Raindrop_voidInit();  // Get raindrop sensor reading
    	        checkRain(isRaining);				 // Take appropriate action based on rain status


    	/*** Check for Incoming Data Over UART ***/
        if (UART_u8IsDataAvailable()) {
            Local_u8Index = 0;
            memset(Local_u8ReceivedBuffer, 0, sizeof(Local_u8ReceivedBuffer)); // Clear buffer before receiving new data

            /*** Receive Data from WiFi Module ***/
            while (1) {
                Local_u8ReceivedBuffer[Local_u8Index] = UART_u8ReceiveDataSync();
                if (Local_u8ReceivedBuffer[Local_u8Index] == '\n') { // End of message
                    Local_u8ReceivedBuffer[Local_u8Index + 1] = '\0'; // Null-terminate
                    break;
                }
                Local_u8Index++;
            }

            /*** Parse Received Data to Extract Command ***/
            if (strstr((char *)Local_u8ReceivedBuffer, "GET /?cmd=") != NULL) {
            	// Locate the command value after "cmd="
                char *commandPtr = strstr((char *)Local_u8ReceivedBuffer, "cmd=") + 4;
                Local_u8Command = *commandPtr;	// Extract the command character

                			  /*** Execute the Command ***/
                              switch (Local_u8Command) {
                                  case 'o': LED_voidLedOn(PORTA, PIN2, VCC); break;   // Turn on LED2
                                  case 'l': LED_voidLedOff(PORTA, PIN2, VCC); break;  // Turn off LED2
                                  case 'a': SERVO_voidRotate1(90); break;             // Rotate Servo 1 to 90°
                                  case 'b': SERVO_voidRotate1(0); break;              // Rotate Servo 1 to 0°
                                  case 'c': SERVO_voidRotate3(0); break;              // Rotate Servo 3 to 0°
                                  case 'd': SERVO_voidRotate3(90); break;             // Rotate Servo 3 to 90°
                                  case 'x': SERVO_voidRotate4(0); break;              // Rotate Servo 4 to 0°
                                  case 'z': SERVO_voidRotate4(90); break;             // Rotate Servo 4 to 90°
                              }

                /*** Send HTTP Response to WiFi Module ***/
                UART_voidSendStringSync("AT+CIPSEND=0,47\r\n");  // Notify WiFi module about response length
                _delay_ms(500);									 // Short delay for stability


                /*** Send HTTP response with a success message ***/
                UART_voidSendStringSync("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nsokr");
                _delay_ms(500);			// Short delay for stability

                /*** Close the TCP connection ***/
                UART_voidSendStringSync("AT+CIPCLOSE=0\r\n");

            }
        }


    }
}
