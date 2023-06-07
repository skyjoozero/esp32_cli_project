#include <stdio.h>
#include "MyGPIO.h"

void setGPIOInputPin(int pinNumber) {
    gpio_config_t myGpioConfig;
    myGpioConfig.pin_bit_mask = 1ULL << pinNumber;
    myGpioConfig.mode = GPIO_MODE_INPUT;
    myGpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    myGpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    myGpioConfig.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&myGpioConfig);
}

void gpioWritePin(int pinNumber, int level) {
    gpio_set_level(pinNumber, level);
}

void setGPIOOutputPin(int pinNumber){
    gpio_config_t myGpioConfig;
    myGpioConfig.pin_bit_mask = 1ULL << pinNumber;
    myGpioConfig.mode = GPIO_MODE_OUTPUT;
    myGpioConfig.pull_up_en = GPIO_PULLUP_DISABLE;
    myGpioConfig.pull_down_en = GPIO_PULLDOWN_ENABLE;
    myGpioConfig.intr_type = GPIO_INTR_DISABLE;

    gpio_config(&myGpioConfig);
}

int gpioReadPin(int pinNumber) {
    return gpio_get_level(pinNumber);
}

void unsetGPIOPin(int pinNumber) {
    gpio_reset_pin(pinNumber);
}