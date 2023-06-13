#include "MyCLI.h"

#define LED_BUILTIN 97
#define MAX_ARGC_VALUE 10

char buffer[128];

void setArgcArgv(int *argc, char **argv, char *commandString) {
    int commandIndex = 0;
    *argc = 0;
    char *p = strtok(commandString, " ");
    while(p != NULL) {
        if(*argc > MAX_ARGC_VALUE)
            break;
        argv[commandIndex] = p;
        *argc += 1;
        p = strtok(NULL, " ");
        commandIndex++;
    }
    argv[commandIndex] = NULL;
}

void excuteCLI(int argc, char **argv) {
    if(strcmp(argv[0], "echo") == 0) {
        echoCommand(argc - 1, &argv[1]);
    } else if(strcmp(argv[0], "gpio") == 0) {
        gpioMode();
    } else if(strcmp(argv[0], "wifi") == 0) {
        wifiMode();
    }
}

void echoCommand(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        sendUartString(argv[i]);
        sendUartString(" ");
    }
    sendUartNewLine();
}

void gpioOutputPinHigh(int argc, char **argv){
    
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOOutputPin(pinNumber);
        gpioWritePin(pinNumber, 1);
        sprintf(buffer, "GPIO %d pin is High", pinNumber);
        sendUartString(buffer);
    }
    sendUartNewLine();
}

void gpioOutputPinLow(int argc, char **argv){
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOOutputPin(pinNumber);
        gpioWritePin(pinNumber, 0);
        sprintf(buffer, "GPIO %d pin is Low", pinNumber);
        sendUartString(buffer);
    }
    sendUartNewLine();
}

void gpioPinReadDigital(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOInputPin(pinNumber);
        sprintf(buffer, "GPIO %d pin is %d", pinNumber, gpioReadPin(pinNumber));
        sendUartString(buffer);
    }
    sendUartNewLine();
}

int excuteGPIO(int argc, char **argv) {
    if(strcmp(argv[0], "exit") == 0) 
        return -1;
    else if(strcmp(argv[0], "on") == 0) 
        gpioOutputPinHigh(argc - 1, &argv[1]);
    else if(strcmp(argv[0], "off") == 0) 
        gpioOutputPinLow(argc - 1, &argv[1]);
    else if(strcmp(argv[0], "read") == 0) 
        gpioOutputPinLow(argc - 1, &argv[1]);
    return 1;
}

int excuteWIFI(int argc, char **argv) {
    if(strcmp(argv[0], "exit") == 0) 
        return -1;
    else if(strcmp(argv[0], "scan") == 0) {
        staInitWifi();
        staRunWifi();
        staScanWifi();
        uint16_t num = staReturnScanedApNum();
        sprintf(buffer, "scanned wifi: %d", num);
        sendUartStringNewLine(buffer);
        staShowScannedWifiList();
    }
    return 1;
}

void gpioMode() {
    int argc = 0;
    char *argv[10];
    char *stringData;
    while(1) {
        sendUartString("(gpio) ");
        stringData = receiveUartStringData();
        setArgcArgv(&argc, argv, stringData);
        if (excuteGPIO(argc, argv) == -1)
            break;
    }
}

void wifiMode() {
    int argc = 0;
    char *argv[10];
    char *stringData;
    while(1) {
        sendUartString("(wifi) ");
        stringData = receiveUartStringData();
        setArgcArgv(&argc, argv, stringData);
        if (excuteWIFI(argc, argv) == -1)
            break;
    }
}

void mainCLI(char *header) {
    int argc = 0;
    char *argv[10];
    char *stringData;
    while(1) {
        sendUartString(header);
        stringData = receiveUartStringData();
        setArgcArgv(&argc, argv, stringData);
        excuteCLI(argc, argv);
    }
}