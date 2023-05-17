#include "MyCLI.h"

#define LED_BUILTIN 97

char** returnCommandArray(char *commandString) {
  char **returnArray = malloc(10 * sizeof(char*));
  for(int i = 0; i < 10; i++) {
    returnArray[i] = malloc(10 * sizeof(char));
  }
  int commandIndex = 0;
  char *p = strtok(commandString, " ");
  while(p != NULL) {
    returnArray[commandIndex] = p;
    // sendUartString(p);
    // sendUartNewLine();
    p = strtok(NULL, " ");
    commandIndex++;
  }
  returnArray[commandIndex] = NULL;
  char** tmp = returnArray;
  free(returnArray);
  return tmp;
}

void excuteCLI(char **commandArray) {
  if(strcmp(commandArray[0], "echo") == 0) {
    echoCommand(commandArray);
  } else if(commandArray[0], "led") {
    ledCommand(commandArray);
  }
}

void echoCommand(char **commandArray) {
  int commandIndex = 1;
  while(commandArray[commandIndex] != NULL) {
    sendUartString(commandArray[commandIndex]);
    sendUartString(" ");
    commandIndex++;
  }
  sendUartNewLine();
}

void ledCommand(char **commandArray) {
  if(strcmp(commandArray[1], "on") == 0) {
    turnOnDefaultLed();
  } else if(strcmp(commandArray[1], "off") == 0) {
    turnOffDefaultLed();
  }
}

void turnOnDefaultLed() {
  neopixelWrite(LED_BUILTIN, 0xFF, 0xFF, 0xFF);
  sendUartStringNewLine("led on!");
}

void turnOffDefaultLed() {
  neopixelWrite(LED_BUILTIN, 0x00, 0x00, 0x00);
  sendUartStringNewLine("led off!");
}