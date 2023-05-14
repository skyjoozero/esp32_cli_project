#include "def.h"

uint32_t baudrate = 115200;
uint64_t timerValue;

esp_timer_handle_t *timerHandler;


void ledOff() {

}
void ledOn() {

}
void ledToggle() {

}
void setUart() {
  int uart_buffer_size = (1024 * 2);
  QueueHandle_t uart_queue;
  uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
  };

  ESP_ERROR_CHECK(uart_param_config(UART_NUM_0, &uart_config));
  ESP_ERROR_CHECK(uart_driver_install(UART_NUM_0, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));
  ESP_ERROR_CHECK(uart_set_pin(UART_NUM_0, GPIO_NUM_37, GPIO_NUM_36, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));
}

void sendUartString(char *string) {
  // ESP_ERROR_CHECK(uart_write_bytes(UART_NUM_0, *string, strlen(string)));
}

void sendUartNewLine() {
  // uart_write_bytes(UART_NUM_0, *string, strlen(string));
}

char *recevieUartData() {

}

void setTimer() {
  
  // struct gptimer_config_t {
  //   .clk_src = GPTIMER_CLK_SRC_DEFAULT,
  //   .direction = GPTIMER_COUNT_UP,
  //   .resolution_hz = 1 * 1000 * 1000, // 1MHz, 1 tick = 1us
  // } timerConfig;

  // gptimer_new_timer(&timerConfig, &gptimer);
  esp_timer_cb_t callBackFunc = sendUartString;
  char *args = "Hello World!\r";
  esp_timer_create_args_t timerSetting = {
  .callback = callBackFunc,
  .arg = args,
  .name = "first timer",
  .dispatch_method = ESP_TIMER_TASK,
  .skip_unhandled_events = true
} ;

  esp_timer_create(&timerSetting, timerHandler);
}

void printUart1Second() {
  
  esp_timer_start_periodic(timerHandler, 1000);
}