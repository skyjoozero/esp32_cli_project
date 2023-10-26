#include "MyUart.h"

char receivedData[128];
int length = 0;
char returnString[128];
int stringIndex = 0;
uint32_t baudrate = 115200;
QueueHandle_t uart_queue;
QueueHandle_t uart_queue1;



void setUart(uint16_t uartNum, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopBit, uint32_t flowControl, uint32_t sourceClk, \
                int txPin, int rxPin, int rtsPin, int ctsPin) {
    int uart_buffer_size = (1024 * 2);
    
    uart_config_t uart_config = {
        .baud_rate = baudrate,
        .data_bits = databits,
        .parity = parity,
        .stop_bits = stopBit,
        .flow_ctrl = flowControl,
        .source_clk = sourceClk,
    };

    ESP_ERROR_CHECK(uart_param_config(uartNum, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(uartNum, txPin, rxPin, rtsPin, ctsPin));
    if (uartNum == UART_NUM_0) 
        ESP_ERROR_CHECK(uart_driver_install(uartNum, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
    else
        ESP_ERROR_CHECK(uart_driver_install(uartNum, uart_buffer_size, uart_buffer_size, 10, &uart_queue1, 0));
    
}

void unSetUart(uint16_t uartNum) {
    uart_driver_delete(uartNum);
}

void sendUartString(uint16_t uartNum, char *string) {
    uart_write_bytes(uartNum, (const char*)string, strlen(string));
}

void sendUartStrings(uint16_t uartNum, int count, ...) {
    va_list list;
   
    va_start(list, count);
    for(int i = 0; i < count; i++) {
        sendUartString(uartNum, va_arg(list, char*));
    }
    
}

void sendUartNewLine(uint16_t uartNum) {
    uart_write_bytes(uartNum, "\r\n", 1);
}

void sendUartStringNewLine(uint16_t uartNum, char *string) {
    uart_write_bytes(uartNum, (const char*)string, strlen(string));
    sendUartNewLine(uartNum);
}

char *receiveUartCharData(uint16_t uartNum) {
  
    ESP_ERROR_CHECK(uart_get_buffered_data_len(uartNum, (size_t*)&length)); 
    if(length > 0) {
    length = uart_read_bytes(uartNum, receivedData, length, 100);
    receivedData[length] = '\0';
    return receivedData;
    } else {
    return NULL;
    }
  
}

char *receiveUartStringData(uint16_t uartNum) {
    stringIndex = 0;

    while(true) {
        char *tempChar = receiveUartCharData(uartNum);
        if (tempChar != NULL) {
            if(strcmp(tempChar, "\r\n") == 0) {
                break;
            } else {
                int i;
                for (i = 0; i < strlen(tempChar) + 1; i++) {
                    returnString[stringIndex + i] = tempChar[i];
                }
                stringIndex++;
            }
        }
    }
    returnString[stringIndex] = '\0';
    return returnString;
}