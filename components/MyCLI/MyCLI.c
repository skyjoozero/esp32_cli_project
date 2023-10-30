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
    } else if(strcmp(argv[0], "gps") == 0) {
        gpsMode();
    }
}

void echoCommand(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        sendUartString(UART_NUM_0, argv[i]);
        sendUartString(UART_NUM_0, " ");
    }
    sendUartNewLine(UART_NUM_0);
}

void gpioOutputPinHigh(int argc, char **argv){
    
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOOutputPin(pinNumber);
        gpioWritePin(pinNumber, 1);
        sprintf(buffer, "GPIO %d pin is High", pinNumber);
        sendUartString(UART_NUM_0, buffer);
    }
    sendUartNewLine(UART_NUM_0);
}

void gpioOutputPinLow(int argc, char **argv){
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOOutputPin(pinNumber);
        gpioWritePin(pinNumber, 0);
        sprintf(buffer, "GPIO %d pin is Low", pinNumber);
        sendUartString(UART_NUM_0, buffer);
    }
    sendUartNewLine(UART_NUM_0);
}

void gpioPinReadDigital(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        int pinNumber = atoi(argv[i]);
        setGPIOInputPin(pinNumber);
        sprintf(buffer, "GPIO %d pin is %d", pinNumber, gpioReadPin(pinNumber));
        sendUartString(UART_NUM_0, buffer);
    }
    sendUartNewLine(UART_NUM_0);
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
        staScanWifi();
        uint16_t num = staReturnScanedApNum();
        sprintf(buffer, "scanned wifi: %d", num);
        sendUartStringNewLine(UART_NUM_0, buffer);
        staShowScannedWifiList();
        // staConnectWifi();
        // staDisconnectWifi();
    } else if(strcmp(argv[0], "connect") == 0) {
        staConnectWifi();
        // staDisconnectWifi();
    }
    return 1;
}

void gpioMode() {
    int argc = 0;
    char *argv[10];
    char *stringData;
    while(1) {
        sendUartString(UART_NUM_0, "(gpio) ");
        stringData = receiveUartStringData(UART_NUM_0);
        setArgcArgv(&argc, argv, stringData);
        if (excuteGPIO(argc, argv) == -1)
            break;
    }
}

void wifiMode() {
    int argc = 0;
    char *argv[10];
    char *stringData;
    staInitWifi();
    while(1) {
        sendUartString(UART_NUM_0, "(wifi) ");
        stringData = receiveUartStringData(UART_NUM_0);
        setArgcArgv(&argc, argv, stringData);
        if (excuteWIFI(argc, argv) == -1)
            break;
    }
}

void gpsMode() {
    int argc = 0;
    int enablePin = 7;
    char *argv[10];
    char *stringData;
    initGPSCommunication();
    ereaseAuxiliaryInform();
    setGPIOInputPin(7);
    while(1) {
        
        gpioWritePin(enablePin, 1);
        stringData = deleteTrashGPSData(getGPSData());
        // if(strcmp(stringData, ""))
        //     sendUartStringNewLine(UART_NUM_0, stringData);
        gpioWritePin(enablePin, 0);

        // free(stringData);
    }
}

void mainCLI(char *header) {
    int argc = 0;
    char *argv[10];
    char *stringData;
    while(1) {
        sendUartString(UART_NUM_0, header);
        stringData = receiveUartStringData(UART_NUM_0);
        setArgcArgv(&argc, argv, stringData);
        excuteCLI(argc, argv);
    }
}