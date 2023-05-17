#include "MyGPIO.h"

gpio_config_t gpioSetting = {};

void setGPIO() {
  gpioSetting.pin_bit_mask = 1ULL << 48;
  gpioSetting.mode = GPIO_MODE_OUTPUT;
  gpioSetting.pull_up_en = GPIO_PULLUP_ENABLE;
  gpioSetting.pull_down_en = GPIO_PULLDOWN_DISABLE;
  gpioSetting.intr_type = GPIO_INTR_DISABLE;

  gpio_config(&gpioSetting);
}

void unSetGPIO() {

}

void turnOnDefaultLed() {
  gpio_set_level(GPIO_NUM_48, 0);
}

void turnOffDefaultLed() {
  gpio_reset_pin(GPIO_NUM_48);
}