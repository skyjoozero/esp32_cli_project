#include "MyUart.h"

uint8_t receivedData[128];
uint8_t receivedString[128];
int dataIndex = 0;
int length = 0;
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
  };

  ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));
  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, 43, 44, -1, -1));
  // ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, GPIO_NUM_37, GPIO_NUM_36, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
}

void unSetUart() {
  uart_driver_delete(UART_NUM_0);
}

void sendUartString(char *string) {
  uart_write_bytes(UART_NUM_0, (const char*)string, strlen(string));
}

void sendUartNewLine() {
  uart_write_bytes(UART_NUM_0, "\r", 1);
}

char *receiveUartCharData() {
  ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t*)&length)); 
  if(length > 0) {
    length = uart_read_bytes(UART_NUM_0, receivedData, length, 100);
    return receivedData;
  } else {
    return NULL;
  }
  
}

char *receiveUartStringData() {
  uint8_t returnString[128];
  int index = 0;
  char *tempChar = receiveUartCharData();
  if(strcmp(tempChar, "\n") == 0) {
    return returnString;
  } else {
    returnString[index] = *tempChar;
    index++;
  }
}