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
  sendUartString("input string: ");
  stringData = receiveUartStringData();
  if (stringData != NULL) {
    sendUartString("you input: ");
    sendUartString(stringData);
    sendUartNewLine();
  }
}
