#include "../Wifi/WIFI.h"
#include "UART_Interface.h"
#include <string.h>

static char receive_Buffer[1024] = {0};
static char send_Buffer[256] = {0};

char* ESP_Send_AT_Command_and_Receive_Response(const char* ATCommand) {
    memset(receive_Buffer, 0, sizeof(receive_Buffer));

    // Send the AT command using UART
    UART_voidSendStringSync((char*)ATCommand);
    UART_voidSendStringSync("\r\n");

    // Receive response
    int index = 0;
    while (index < sizeof(receive_Buffer) - 1) {
        receive_Buffer[index] = UART_u8ReceiveDataSync();
        if (receive_Buffer[index] == '\n') break;
        index++;
    }
    receive_Buffer[index + 1] = '\0'; // Null-terminate

    return receive_Buffer;
}

bool ESP_Init(const char* mode) {
    if (strcmp(ESP_Send_AT_Command_and_Receive_Response("AT+RST"), "OK") != 0) {
        return false;
    }

    memset(send_Buffer, 0, sizeof(send_Buffer));
    snprintf(send_Buffer, sizeof(send_Buffer), "AT+CWMODE=%s", mode);
    if (strcmp(ESP_Send_AT_Command_and_Receive_Response(send_Buffer), "OK") != 0) {
        return false;
    }

    return true;
}

bool ESP_Connect_AP(const char* ssid, const char* password) {
    memset(send_Buffer, 0, sizeof(send_Buffer));
    snprintf(send_Buffer, sizeof(send_Buffer), "AT+CWJAP=\"%s\",\"%s\"", ssid, password);
    const char* response = ESP_Send_AT_Command_and_Receive_Response(send_Buffer);
    return strstr(response, "WIFI CONNECTED") != NULL;
}

bool ESP_Start_Server(const char* port) {
    if (strcmp(ESP_Send_AT_Command_and_Receive_Response("AT+CIPMUX=1"), "OK") != 0) {
        return false;
    }

    memset(send_Buffer, 0, sizeof(send_Buffer));
    snprintf(send_Buffer, sizeof(send_Buffer), "AT+CIPSERVER=1,%s", port);
    if (strcmp(ESP_Send_AT_Command_and_Receive_Response(send_Buffer), "OK") != 0) {
        return false;
    }

    return true;
}

bool ESP_Send_Data(const char* data, const char* channel) {
    memset(send_Buffer, 0, sizeof(send_Buffer));
    snprintf(send_Buffer, sizeof(send_Buffer), "AT+CIPSEND=%s,%d", channel, (int)strlen(data));

    if (strcmp(ESP_Send_AT_Command_and_Receive_Response(send_Buffer), ">") != 0) {
        return false;
    }

    UART_voidSendStringSync((char*)data);
    UART_voidSendStringSync("\r\n");

    const char* response = ESP_Send_AT_Command_and_Receive_Response("");
    return strstr(response, "SEND OK") != NULL;
}

bool ESP_Close_Connection(const char* channel) {
    memset(send_Buffer, 0, sizeof(send_Buffer));
    snprintf(send_Buffer, sizeof(send_Buffer), "AT+CIPCLOSE=%s", channel);
    return strcmp(ESP_Send_AT_Command_and_Receive_Response(send_Buffer), "OK") == 0;
}

void ESP_Clear_Buffer() {
    memset(receive_Buffer, 0, sizeof(receive_Buffer));
}
