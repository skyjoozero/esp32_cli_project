#include <stdio.h>
#include "MyGPIO.h"

void setGPIOInputPin(int pinNumber) {
    gpioConfig.pin_bit_mask = 1ULL << pinNumber;
    gpioConfig.mode = GPIO_MODE_INPUT;
    gpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpioConfig.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&gpioConfig);
}

void gpioWritePin(int pinNumber, int level) {
    gpio_set_level(pinNumber, level);
}

void setGPIOOutputPin(int pinNumber){
    gpioConfig.pin_bit_mask = 1ULL << pinNumber;
    gpioConfig.mode = GPIO_MODE_OUTPUT;
    gpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    gpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    gpioConfig.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&gpioConfig);
}

int gpioReadPin(int pinNumber) {
    return gpio_get_level(pinNumber);
}

void unsetGPIOPin(int pinNumber) {
    gpio_reset_pin(pinNumber);
}