#include "def.h"

uint64_t nowTime = 0;
char *helloSring = "hello\r";
char sendString[64];
char *stringData;
int delayed = 1;

//todo: 영어 입력만 받도록 하기

void setup() {
  // put your setup code here, to run once:
  setUart();
  // setGPIO();
}

void loop() {
  // put your main code here, to run repeatedly:
  sendUartString("esp32>>");
  stringData = receiveUartStringData();
  char **commands = returnCommandArray(stringData);
  excuteCLI(commands);
}
