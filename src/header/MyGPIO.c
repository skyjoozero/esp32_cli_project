#include "MyGPIO.h"

gpio_config_t gpioSetting = {};

void setGPIO(int pinNum) {
  gpioSetting.pin_bit_mask = (1ULL << pinNum);
  gpioSetting.mode = GPIO_MODE_OUTPUT;
  gpioSetting.pull_up_en = GPIO_PULLUP_DISABLE;
  gpioSetting.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpioSetting.intr_type = GPIO_INTR_DISABLE;
  gpio_config(&gpioSetting);
}

void unSetGPIO() {

}
