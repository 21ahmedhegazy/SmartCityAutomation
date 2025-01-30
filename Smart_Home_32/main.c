/************************************/
/* File      : main.c               */
/* Author    : Ahmed Hegazy          */
/* Date 	 : 8/10/2023            */
/* Version 	 : V1.0                 */
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
 #include "HAL/LCD/LCD_Interface.h"
 #include "HAL/DC_MOTOR/Motor_Interface.h"
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
u8 Local_u8Command = 0;          // Command extracted from GET request

void checkRain(void);
u8 UART_u8IsDataAvailable(void);

void main(void) {
    // Initialize peripherals
    LED_voidLedInit(PORTA, PIN0); // Initialize LED 0
    LED_voidLedInit(PORTA, PIN1); // Initialize LED 1
    LED_voidLedInit(PORTA, PIN2); // Initialize LED 2
    LED_voidLedInit(PORTA, PIN3); // Initialize LED for raindrop sensor
    SERVO_voidInit();             // Initialize Servo Motor
    UART_voidInit();              // Initialize UART

    Wifi_voidInit();

    while (1) {
        checkRain();

        // Check if data is available on the serial port
        if (UART_u8IsDataAvailable()) {
            // Receive data from the Wi-Fi module
            Local_u8Index = 0;
            memset(Local_u8ReceivedBuffer, 0, sizeof(Local_u8ReceivedBuffer)); // Clear buffer

            while (1) {
                Local_u8ReceivedBuffer[Local_u8Index] = UART_u8ReceiveDataSync();
                if (Local_u8ReceivedBuffer[Local_u8Index] == '\n') { // End of message
                    Local_u8ReceivedBuffer[Local_u8Index + 1] = '\0'; // Null-terminate
                    break;
                }
                Local_u8Index++;
            }

            // Check if the data contains "GET /?cmd="
            if (strstr((char *)Local_u8ReceivedBuffer, "GET /?cmd=") != NULL) {
                // Extract the command after "cmd="
                char *commandPtr = strstr((char *)Local_u8ReceivedBuffer, "cmd=") + 4;
                Local_u8Command = *commandPtr;

                // Perform the action based on the extracted command
                switch (Local_u8Command) {
                    case 'b': // Open LED
                        LED_voidLedOn(PORTA, PIN2, VCC);
                        break;
                    case 'a': // Close LED
                        LED_voidLedOff(PORTA, PIN2, VCC);
                        break;
                    case 'c': // Open Door
                        DOOR_voidDoorOpen();
                        break;
                    case 'o': // Close Door
                        DOOR_voidDoorClose();
                        break;
                    default: // Invalid or unsupported command
                        break;
                }

                // Send response back to the client
                UART_voidSendStringSync("AT+CIPSEND=0,20\r\n");  // Prepare to send response
                _delay_ms(100);
                UART_voidSendStringSync("HTTP/1.1 200 OK\r\n\r\nCommand Executed");
            }
        }
    }
}






