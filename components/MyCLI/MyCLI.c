#include "MyCLI.h"

#define LED_BUILTIN 97
#define MAX_ARGC_VALUE 10

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
    }
}

void echoCommand(int argc, char **argv) {
    for(int i = 0; i < argc; i++) {
        sendUartString(argv[i]);
        sendUartString(" ");
    }
    sendUartNewLine();
}

int excuteGPIO(int argc, char **argv) {
    if(strcmp(argv[0], "exit") == 0) 
        return -1;
    // else if(strcmp(argv[0], "gpio") == 0) 
    //     gpioMode();
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