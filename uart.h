#ifndef UART_HEADER
#define UART_HEADER

#include <stdint.h>
#include <string.h>
#include <driver/uart.h>
#include <hal/gpio_types.h>

void setUart();
void unSetUart();
void sendUartString(char *string);
void sendUartNewLine();
char *receiveUartData();

#endif