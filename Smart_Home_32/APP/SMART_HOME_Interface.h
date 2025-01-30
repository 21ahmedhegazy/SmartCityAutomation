/**************************************/
/* File      : SMART_HOME_Interface.c */
/* Author    : Ahmed Karam            */
/* Date 	 : 8/10/2023              */
/* Version 	 : V1.0                   */
/**************************************/
#ifndef APP_SMART_HOME_INTERFACE_H_
#define APP_SMART_HOME_INTERFACE_H_


void LED_voidLed1ON(void);
void LED_voidLed2ON(void);
void LED_voidLed3ON(void);
void LED_voidLed4ON(void);

void LED_voidLed1OFF(void);
void LED_voidLed2OFF(void);
void LED_voidLed3OFF(void);
void LED_voidLed4OFF(void);

void DOOR_voidDoorOpen(void);
void DOOR_voidDoorClose(void);

void FAN_voidFanOpen(void);
void FAN_voidFanClose(void);

void ALARM_voidBuzzerOn(void);

void Wifi_voidInit();

void checkRain();


#endif /* APP_SMART_HOME_INTERFACE_H_ */
