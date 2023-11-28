#include "MyGPSModule.h"


char *header = "$PGKC";
char *footer = "\x0d\x0a";

char *responseMsg(char *commandOfMsg, char *arg);

char *systemReboot(char *arg1, char *arg2) {
    char *command = "030";
    char *commandString = appendStrings(header, command, ",", arg1, ",", arg2, "*", "checksum", footer);

    //sendUartString(UART_NUM_1, commandString);
    free(commandString);

    return "";
}

char *ereaseAuxiliaryInform() {
    char *command = "040";
    char *commandString = appendStrings(header, command, "*", "checksum", footer);

    // printf("%s", commandString);
    free(commandString);

    return "";
}

char *lowPowerMode(char *arg1) {
    char *command = "051";
    char *commandString = appendStrings(header, command, ",", arg1, "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}

char *setMessageInterval(char *arg1) {
    char *command = "101";
    char *commandString = appendStrings(header, command, ",", arg1, "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}

char *periodicLowPowerMode(char *arg1, char *arg2, char *arg3) {
    char *command = "105";
    char *commandString = strcmp(arg1, "8") == 0 ?
                        appendStrings(header, command, ",", arg1, "*", "checksum", footer):
                        appendStrings(header, command, ",", arg1, ",", arg2, ",", arg3,  "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}


char *setStarSearchMode(char *arg1, char *arg2, char *arg3, char *arg4) {
    char *command = "115";
    char *commandString = appendStrings(header, command, ",", arg1, ",", arg2, ",", arg3, ",", arg4, "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}


char *serialPortParameterSetting(char *arg1, char *arg2, char *arg3) {
    char *command = "146";
    char *commandString = appendStrings(header, command, ",", arg1, ",", arg2, ",", arg3, "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}


char *setNMEAOutput(char *arg1) {
    char *command = "147";
    char *commandString = appendStrings(header, command, ",", arg1, "*", "checksum", footer);

    printf("%s", commandString);
    free(commandString);

    return "";
}


char* appendStrings(const char* first, ...) {
    // Initialize the argument list
    va_list args;
    va_start(args, first);

    // Calculate the total length of the concatenated string
    int totalLength = 0;
    const char* current = first;
    while (current != NULL) {
        totalLength += (strcmp(current, "checksum") == 0 ?
                        2 :
                        snprintf(NULL, 0, "%s", current));
        current = va_arg(args, const char*);
    }

    // Allocate memory for the concatenated string
    char* result = (char*)malloc(totalLength + 1);

    // Concatenate the arguments into the result string
    int currentPosition = 0;
    va_start(args, first);  // Restart the argument list
    current = first;
    while (current != NULL) {
        currentPosition += strcmp(current, "checksum") == 0 ?
                            snprintf(result + currentPosition, totalLength - currentPosition + 1, "%02X", getChecksum(result)) :
                            snprintf(result + currentPosition, totalLength - currentPosition + 1, "%s", current);
        current = va_arg(args, const char*);
    }

    // Clean up the argument list
    va_end(args);

    return result;
}


//void appendStrings(char *returnStr, char **returnStrAddr,  ...) {
//    va_list args;
//    char check[3];
//    char *temp = "";
////    char **tempAddr;
//
//    va_start(args, returnStrAddr);
//
//    while (temp != NULL) {
//        temp = va_arg(args, char *);
////        tempAddr = &returnStr;
//        int str1Len = strlen(returnStr);
//
//
//        if(strcmp(temp, "checksum") == 0) {
//            sprintf(check, "%02X", getChecksum(returnStr));
//            int str2Len = strlen(check);
//            *returnStrAddr = realloc(*returnStrAddr, sizeof(char) * (str1Len + str2Len + 1));
//            memcpy(returnStr, temp, str1Len);
//            memcpy(returnStr + str1Len, temp, str2Len + 1);
//        } else {
//            int str2Len = strlen(temp);
//            *returnStrAddr = realloc(*returnStrAddr, sizeof(char) * (str1Len + str2Len + 1));
//            memcpy(*returnStrAddr, returnStr, str1Len);
//            memcpy(*returnStrAddr + str1Len, temp, str2Len + 1);
//        }
//
//        returnStr[-1] = '\0';
//    }
//}



//void appendString(char *str1, char *str2, char **returnStr) {
//
//    int str1Len = strlen(str1);
//    int str2Len = strlen(str2);
//    realloc(*returnStr, sizeof(char) * (str1Len + str2Len + 1));
////    *returnStr = (char *) malloc(sizeof(char) * (str1Len + str2Len + 1));
//
//    if (returnStr == NULL) {
//        returnStr = NULL;
//    }
//
//    memcpy(*returnStr, str1, str1Len);
//    memcpy(*returnStr + str1Len, str2, str2Len + 1);
//
//}


uint8_t getChecksum(char *string) {

    //string[0] = $, it is not include
    //string[-1] = *, it is not include
//    string = &string[1];

    uint8_t check = 0;

    for(int i = 1; i < strlen(string) - 1; i++) {
        check ^= (uint8_t) string[i];
    }

    return check;
}



void initGPSCommunication() {
    setUart(UART_NUM_1, 9600, UART_DATA_8_BITS, UART_PARITY_DISABLE, UART_STOP_BITS_1, UART_HW_FLOWCTRL_DISABLE, UART_SCLK_DEFAULT, 4, 5, -1, -1);
    // char *a = systemReboot("4", "2");
}

char *getGPSData() {
    char *string = "";
    size_t dataLen = 0;
    uart_get_buffered_data_len(UART_NUM_1, &dataLen);
    if(dataLen) {
        string = receiveUartCharData(UART_NUM_1);
        return string;
    }
    return string;
}

char *deleteTrashGPSData(char *string) {
    char *GNGGAHeader = "GNGGA";
    char *returnString = "";
    char *mainString = "";
    GNGGAData_t gnggaData;    

    char tempString[500];
    // printf("!");
    changeCharPointerToCharArray(string, tempString);

    char *p = strtok(tempString, "$");

    while(p != NULL) {
        // printf("%s\n", p);
        if (strncmp(p, GNGGAHeader, strlen(GNGGAHeader)) == 0) {
            // printf("%s\n", p);
            // mainString = appendStrings(mainString, p);
            // printf("%s\n", p);
            // free(mainString);

            // sendUartString(UART_NUM_0, p);
            getGNGGAData(&gnggaData, p);

            sendUartString(UART_NUM_0, "UTC time: ");
            sendUartStringNewLine(UART_NUM_0, gnggaData.UTCDate);

            sendUartString(UART_NUM_0, "latitude: ");
            sendUartStringNewLine(UART_NUM_0, gnggaData.latitude);

            sendUartString(UART_NUM_0, "longtitude: ");
            sendUartStringNewLine(UART_NUM_0, gnggaData.longtitude);

            return p;
        }

        p = strtok(NULL, "$");
    }

    return "";

}

void changeCharPointerToCharArray(char *string1, char sting2[]) {
    int i = 0;
//    char returnString[100];

    while (string1[i] != '\0') {
        sting2[i] = string1[i];
        i++;
    }

    sting2[i] = '\0';

//    return returnString;
}

void getGNGGAData(GNGGAData_t *structData, char *stringData) {
    char *p = strtok(stringData, ",");
    p = strtok(NULL, ",");

    //memcpy(structData->UTCDate, p, sizeof(p));

    structData->UTCDate = p;
    p = strtok(NULL, ",");

    structData->latitude = p;
    p = strtok(NULL, ",");

    structData->NSIndication = p;
    p = strtok(NULL, ",");

    structData->longtitude = p;
    p = strtok(NULL, ",");

    structData->EWIndication = p;
    p = strtok(NULL, ",");

    structData->positioningInstructions = p;
    p = strtok(NULL, ",");

    structData->numberOfSatellites = p;
    p = strtok(NULL, ",");

    structData->HDOP = p;
    p = strtok(NULL, ",");

    structData->MSLAmplitude = p;
    p = strtok(NULL, ",");

    structData->unit = p;
    p = strtok(NULL, ",");

    structData->theEarth = p;
    p = strtok(NULL, ",");

    structData->differentialTime = p;
    p = strtok(NULL, ",");

    structData->differentialID = p;
    p = strtok(NULL, ",");
}