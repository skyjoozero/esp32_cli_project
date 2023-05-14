#include "def.h"

uint64_t nowTime = 0;
char *helloSring = "hello\r";


void setup() {
  // put your setup code here, to run once:
  setUart();
  setTimer();
}

void loop() {
  // put your main code here, to run repeatedly:
  // printUart1Second();
  // sendUartString(helloSring);
  uart_write_bytes(UART_NUM_0, (char*)helloSring, strlen(helloSring));
  delay(1000);
}
