#ifndef MY_CLI_HEADER
#define MY_CLI_HEADER

#include <string.h>
#include <malloc.h>
#include "MyUart.h"

char **returnCommandArray(char *commandString);

void excuteCLI(char **commandArray);

void echoCommand(char **commandArray);

void ledCommand(char **commandArray);

void gpioMode();

void turnOnDefaultLed();

void turnOffDefaultLed();

void mainCLI(char *header);

#endif