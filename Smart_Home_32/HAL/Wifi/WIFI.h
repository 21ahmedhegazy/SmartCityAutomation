#ifndef HAL_WIFI_H_
#define HAL_WIFI_H_

#include "UART_Interface.h"
#include <stdbool.h>
#include <stdint.h>

#define MAX_NUMBER_OF_APs 20
#define MAX_LEN_OF_SINGLE_AP_SSID 32
#define MAX_LEN_OF_RECV_DATA 256

// Function prototypes
char* ESP_Send_AT_Command_and_Receive_Response(const char* ATCommand);
bool ESP_Init(const char* mode);
bool ESP_Connect_AP(const char* ssid, const char* password);
bool ESP_Start_Server(const char* port);
bool ESP_Send_Data(const char* data, const char* channel);
bool ESP_Close_Connection(const char* channel);
void ESP_Clear_Buffer();

#endif /* HAL_WIFI_H_ */
