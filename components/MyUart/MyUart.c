#include "MyUart.h"

char receivedData[128];
int length = 0;
char returnString[128];
int stringIndex = 0;
uint32_t baudrate = 115200;

void setUart() {
    int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };

    ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, 43, 44, -1, -1));
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
}

void unSetUart() {
    uart_driver_delete(UART_NUM_0);
}

void sendUartString(char *string) {
    uart_write_bytes(UART_NUM_0, (const char*)string, strlen(string));
}

void sendUartNewLine() {
    uart_write_bytes(UART_NUM_0, "\r\n", 1);
}

void sendUartStringNewLine(char *string) {
    uart_write_bytes(UART_NUM_0, (const char*)string, strlen(string));
    sendUartNewLine();
}

char *receiveUartCharData() {
  
    ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t*)&length)); 
    if(length > 0) {
    length = uart_read_bytes(UART_NUM_0, receivedData, length, 100);
    receivedData[length] = '\0';
    return receivedData;
    } else {
    return NULL;
    }
  
}

char *receiveUartStringData() {
    stringIndex = 0;

    while(true) {
        char *tempChar = receiveUartCharData();
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