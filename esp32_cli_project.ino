#include "def.h"

uint64_t nowTime = 0;
char *helloSring = "hello\r";
char sendString[64];
char *stringData;
int delayed = 1;


void setup() {
  // put your setup code here, to run once:
  setUart();
}

void loop() {
  // put your main code here, to run repeatedly:
  stringData = receiveUartCharData();
  // sendUartString(stringData);
  if (stringData != NULL) {
    sendUartNewLine();
    sendUartString("you input: ");
    sendUartString(stringData);
    sendUartNewLine();
    // uart_write_bytes(UART_NUM_0,(const char*) helloSring, strlen(helloSring));
  }
  // sendUartString(stringData);
  // delay(1000);
}
