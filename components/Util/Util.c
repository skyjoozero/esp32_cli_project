#include "Util.h"

void delay_ms(int ms) {
    vTaskDelay(ms / portTICK_PERIOD_MS);
}
