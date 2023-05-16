// #include "MyTimer.h"


// uint64_t timerValue;

// esp_timer_handle_t *timerHandler;


// void ledOff() {

// }
// void ledOn() {

// }
// void ledToggle() {

// }


// void setTimer() {
  
//   // struct gptimer_config_t {
//   //   .clk_src = GPTIMER_CLK_SRC_DEFAULT,
//   //   .direction = GPTIMER_COUNT_UP,
//   //   .resolution_hz = 1 * 1000 * 1000, // 1MHz, 1 tick = 1us
//   // } timerConfig;

//   // gptimer_new_timer(&timerConfig, &gptimer);
//   esp_timer_cb_t callBackFunc = sendUartString;
//   char *args = "Hello World!\r";
//   esp_timer_create_args_t timerSetting = {
//   .callback = callBackFunc,
//   .arg = args,
//   .name = "first timer",
//   .dispatch_method = ESP_TIMER_TASK,
//   .skip_unhandled_events = true
// } ;

//   esp_timer_create(&timerSetting, timerHandler);
// }

// void printUart1Second() {
  
//   esp_timer_start_periodic(timerHandler, 1000);
// }