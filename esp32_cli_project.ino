#include "def.h"

uint64_t nowTime = 0;
char *helloSring = "hello\r";
char *stringData;


void setup() {
  // put your setup code here, to run once:
  setUart();
}

void loop() {
  // put your main code here, to run repeatedly:
  // stringData = receiveUartData();
  // if (stringData != NULL) {
  //   sendUartString(stringData);
  //   uart_write_bytes(UART_NUM_0,(const char*) helloSring, strlen(helloSring));
  // }
  const    uart_port_t uart_num = UART_NUM_0; 
  uint8_t    data[128];
  int    length = 0;
  ESP_ERROR_CHECK(uart_get_buffered_data_len(uart_num, (size_t*)&length)); 
  length = uart_read_bytes(uart_num, data, length, 1000);
  uart_write_bytes(UART_NUM_0, (const char*)helloSring, strlen(helloSring));
  delay(1000);
}
