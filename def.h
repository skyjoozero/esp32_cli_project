#ifdef __cplusplus
extern "C" {
#endif

#ifndef DEF_INIT
#define DEF_INIT

#define DEFAULT_LED_PORT_NUM

#include <stdint.h>
#include <driver/uart.h>
#include <hal/gpio_types.h>
#include <esp_timer.h>

void ledOff();
void ledOn();
void ledToggle();

void setUart();
void sendUartString(char *string);
void sendUartNewLine();
char *recevieUart1Data();

void setTimer();
void printUart1Second();

#endif

#ifdef __cplusplus
}
#endif