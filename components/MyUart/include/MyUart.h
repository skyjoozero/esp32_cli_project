#ifndef UART_HEADER
#define UART_HEADER

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <driver/uart.h>
#include "Util.h"
// #include <hal/gpio_types.h>


void setUart2();


void setUart(uint16_t uartNum, uint32_t baudrate, uint32_t databits, uint32_t parity, uint32_t stopBit, uint32_t flowControl, uint32_t sourceClk, int txPin, int rxPin, int rtsPin, int ctsPin);
void unSetUart(uint16_t uartNum);
void sendUartString(uint16_t uartNum, char *string);
void sendUartStrings(uint16_t uartNum, int count, ...);
void sendUartNewLine(uint16_t uartNum);
void sendUartStringNewLine(uint16_t uartNum, char *string);
char *receiveUartCharData(uint16_t uartNum);
char *receiveUartStringData(uint16_t uartNum); //return strig before input enter

#endif