#include "def.h"

TaskHandle_t handle;
char *stringData;

void app_main(void)
{
    setUart();
    while (1)
    {
        sendUartString("esp32>>");
        stringData = receiveUartStringData();
        char **commands = returnCommandArray(stringData);
        excuteCLI(commands);
        free(commands);
    }
    
}

