#ifndef MY_WIFI_H
#define MY_WIFI_H

#define MAX_WIFI_SEARCH 10
#define DEFAULT_SCAN_LIST_SIZE MAX_WIFI_SEARCH

#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_system.h"
#include "MyUart.h"


void staInitWifi();
void staScanWifi();
static void print_auth_mode(int authmode);
static void print_cipher_type(int pairwise_cipher, int group_cipher);
uint16_t staReturnScanedApNum();
void staShowScannedWifiList();
void staConnectWifi();
void staDisconnectWifi();
void staStopWifi();
void staDeInitWifi();


#endif