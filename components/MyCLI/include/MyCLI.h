#ifndef MY_CLI_HEADER
#define MY_CLI_HEADER

#include <string.h>
#include <malloc.h>
#include "MyUart.h"

void setArgcArgv(int *argc, char **argv, char *commandString);

void excuteCLI(int argc, char **argv);

void echoCommand(int argc, char **argv);

int excuteGPIO(int argc, char **argv);

void gpioMode();

void mainCLI(char *header);

#endif