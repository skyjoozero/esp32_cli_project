#include "def.h"

void app_main(void) {

    setUart(UART_NUM_0, 115200, UART_DATA_8_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1, UART_HW_FLOWCTRL_DISABLE, UART_SCLK_DEFAULT, 43, 44, -1, -1);
    while (1) {

        mainCLI("esp32>> ");
        
    }
    
}

