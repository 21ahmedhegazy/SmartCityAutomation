/**************************************/
/* File      : SMART_HOME_Interface.c */
/* Author    : Ahmed Hegazy            */
/* Version 	 : V2.0                   */
/**************************************/
#ifndef APP_SMART_HOME_INTERFACE_H_
#define APP_SMART_HOME_INTERFACE_H_

void Wifi_voidInit();
u8 Raindrop_voidInit(void);
u8 checkRain(u8 isRaining);
void ReadSmokeSensor(void);
void SmokeSensor (void);

#endif /* APP_SMART_HOME_INTERFACE_H_ */
