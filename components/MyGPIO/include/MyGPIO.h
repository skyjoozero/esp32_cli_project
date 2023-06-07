#ifndef MY_GPIO_HEADER
#define MY_GPIO_HEADER

#include "driver/gpio.h"

void setGPIOInputPin(int pinNumber);

// level 0-low 1-high
void gpioWritePin(int pinNumber, int level);
void setGPIOOutputPin(int pinNumber);
int gpioReadPin(int pinNumber);
void unsetGPIOPin(int pinNumber);

#endif