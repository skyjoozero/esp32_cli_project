#ifndef MY_CLI_HEADER
#define MY_CLI_HEADER

#include <string.h>
#include "MyUart.h" // 지우기 

char **returnCommandArray(char *commandString);

void excuteCLI(char **commandArray);

void echoCommand(char **commandArray);

void LedCommand(char **commandArray);

void turnOnDefaultLed();

void turnOffDefaultLed();


#endif