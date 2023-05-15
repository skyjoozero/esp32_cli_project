#include "uart.h"

uint32_t baudrate = 115200;
int length = 0;

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
  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, GPIO_NUM_37, GPIO_NUM_36, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
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

char *receiveUartData() {
  uint8_t receivedData[128];
  ESP_ERROR_CHECK(uart_get_buffered_data_len(UART_NUM_0, (size_t*)&length)); 
  if(length > 0) {
    sendUartString("comeData");
    length = uart_read_bytes(UART_NUM_0, receivedData, length, 100);
    // uart_flush(UART_NUM_0);
    return receivedData;
  } else {
    return NULL;
  }
  
}