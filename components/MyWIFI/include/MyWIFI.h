#ifndef MY_WIFI_H
#define MY_WIFI_H

#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "MyUart.h"


void staInitWifi();
void staRunWifi();
void staScanWifi();
uint16_t staReturnScanedApNum();
void staShowScannedWifiList();
void staStopWifi();
void staDeInitWifi();


#endif