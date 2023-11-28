#include <stdio.h>
#include "NeoPixelCounter.h"

gptimer_handle_t timerHandle = NULL;
gptimer_config_t timerConfig = {
    .clk_src = GPTIMER_CLK_SRC_DEFAULT,
    .direction = GPTIMER_COUNT_UP,
    .resolution_hz = 1 * 10 * 1000,
};


void settingCounter(void) {
    gptimer_new_timer(&timerConfig, &timerHandle);
}

void enableCounter(void) {
    gptimer_enable(timerHandle);
}

void startCounter(void) {
    gptimer_start(timerHandle);
}