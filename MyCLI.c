#include "MyCLI.h"

char** returnCommandArray(char *commandString) {
  char **returnArray = malloc(10 * sizeof(char*));
  for(int i = 0; i < 10; i++) {
    returnArray[i] = malloc(10 * sizeof(char));
  }
  int commandIndex = 0;
  char *p = strtok(commandString, " ");
  while(p != NULL) {
    returnArray[commandIndex] = p;
    // sendUartString(p);
    // sendUartNewLine();
    p = strtok(NULL, " ");
    commandIndex++;
  }
  returnArray[commandIndex] = NULL;
  char** tmp = returnArray;
  free(returnArray);
  return tmp;
}

void excuteCLI(char **commandArray) {
  if(strcmp(commandArray[0], "echo") == 0) {
    echoCommand(commandArray);
  }
}

void echoCommand(char **commandArray) {
  int commandIndex = 1;
  while(commandArray[commandIndex] != NULL) {
    sendUartString(commandArray[commandIndex]);
    sendUartString(" ");
    commandIndex++;
  }
  sendUartNewLine();
}