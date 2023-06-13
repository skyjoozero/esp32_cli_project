#ifndef MY_CLI_HEADER
#define MY_CLI_HEADER

#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "MyUart.h"
#include "MyGPIO.h"
#include "MyWIFI.h"

void setArgcArgv(int *argc, char **argv, char *commandString);

void excuteCLI(int argc, char **argv);

void echoCommand(int argc, char **argv);

void gpioOutPutPinHigh(int argc, char **argv);

void gpioOutputPinLow(int argc, char **argv);

void gpioPinReadDigital(int argc, char **argv);

int excuteGPIO(int argc, char **argv);

int excuteWIFI(int argc, char **argv);

void gpioMode();

void wifiMode();

void mainCLI(char *header);

#endif