#ifndef MY_GPIO_HEADER
#define MY_GPIO_HEADER

#include <driver/gpio.h>
#include <esp32-hal-rgb-led.h>
#include <pins_arduino.h>

void setGPIO(int pinNum);
void unSetGPIO();

#endif