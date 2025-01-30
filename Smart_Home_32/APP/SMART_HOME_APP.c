/************************************/
/* File      : SMART_HOME_APP.c     */
/* Author    : Ahmed Hegazy        */
/* Date 	 : 8/10/2023            */
/* Version 	 : V1.0                 */
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
 #include "../HAL/LCD/LCD_Interface.h"
 #include "../HAL/DC_MOTOR/Motor_Interface.h"
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

void LED_voidLed1ON(void)
{
	LED_voidLedOn(PORTB ,PIN5 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_1 ON");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed2ON(void)
{
	LED_voidLedOn(PORTB ,PIN6 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_2 ON");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed3ON(void)
{
	LED_voidLedOn(PORTB ,PIN7 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_3 ON");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed4ON(void)
{
	LED_voidLedOn(PORTA ,PIN2 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_4 ON");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}


void LED_voidLed1OFF(void)
{
	LED_voidLedOff(PORTB ,PIN5,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_1 OFF");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed2OFF(void)
{
	LED_voidLedOff(PORTB ,PIN6 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_2 OFF");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed3OFF(void)
{
	LED_voidLedOff(PORTB ,PIN7 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_3 OFF");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void LED_voidLed4OFF(void)
{
	LED_voidLedOff(PORTA ,PIN2 ,VCC);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("LED_4 OFF");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}


void DOOR_voidDoorOpen(void)
{
	SERVO_voidRotate(90);
	LED_voidLedOff(PORTA,PIN1,VCC);
			BUZZER_voidBuzzerON(PORTA ,PIN0);
			_delay_ms(100);
			BUZZER_voidBuzzerOFF(PORTA ,PIN0);
		_delay_ms(1000);


}
void DOOR_voidDoorClose(void)
{
	SERVO_voidRotate(0);
	LED_voidLedOn(PORTA,PIN1,VCC);
			BUZZER_voidBuzzerON(PORTA ,PIN0);
			_delay_ms(100);
			BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}

void FAN_voidFanOpen(void)
{
	DCMotor_voidMotorON(PORTA ,PIN1);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("FAN ON ..");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}
void FAN_voidFanClose(void)
{
	DCMotor_voidMotorOFF(PORTA ,PIN1);
	LCD_voidWriteCommand(Lcd_Clear);
	LCD_voidWriteString("FAN OFF ..");
	BUZZER_voidBuzzerON(PORTA ,PIN0);
	_delay_ms(100);
	BUZZER_voidBuzzerOFF(PORTA ,PIN0);
	_delay_ms(1000);
}

void ALARM_voidBuzzerOn(void)
{
	for(u8 counter = 0 ; counter < 50 ; counter++)
		{
			BUZZER_voidBuzzerToggel(PORTA ,PIN0);
			_delay_ms(50);
		}
}

// Send initialization commands to the Wi-Fi module
void Wifi_voidInit()
{
	  UART_voidSendStringSync("AT+CIPMUX=1\r\n");  // Enable multiple connections
	  _delay_ms(1000);                             // Wait for command to process
	  UART_voidSendStringSync("AT+CIPSERVER=1,80\r\n");  // Start server on port 80
	  _delay_ms(1000);
}

void checkRain()
{
    // Initialize raindrop sensor pin
    u8 isRaining = DIO_u8GetPinValue(PORTA, PIN4) == 0;

    if (isRaining) { // Active LOW signal indicates rain
        LED_voidLedOn(PORTA, PIN3, VCC);
    } else {
        LED_voidLedOff(PORTA, PIN3, VCC);
    }
}
