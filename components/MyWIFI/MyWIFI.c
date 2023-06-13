#include "MyWIFI.h"

uint16_t number = 0;
uint16_t apCount = 0;
char wifiBuffer[128];
wifi_ap_record_t apInfo[10];

static const char *TAG = "scan";

void staInitWifi() {
    const wifi_init_config_t wifiConfig = WIFI_INIT_CONFIG_DEFAULT();
    memset(apInfo, 0, sizeof(apInfo));
    nvs_flash_init();
    esp_wifi_init(&wifiConfig);
    esp_wifi_set_mode(WIFI_MODE_STA);
}

void staRunWifi() {
    esp_wifi_start();
}

void staScanWifi() {
    // wifi_scan_config_t scanConfig;
    // wifi_active_scan_time_t actScanTimeConfig = {
    //     .min = 
    // }
    // wifi_scan_time_t scanTimeConfig = {
    //     .active = 
    // }
    // scanConfig.show_hidden = true;
    // scanConfig.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    // scanConfig.scan_time = 
    esp_wifi_scan_start(NULL, true);
    esp_wifi_scan_get_ap_num(&apCount);
    esp_wifi_scan_get_ap_records(&number, apInfo);
}

uint16_t staReturnScanedApNum() {
    return apCount;
}

void staShowScannedWifiList() {
    // for(int i = 0; i < apCount; i++) {
    //     sprintf(wifiBuffer, "%d ssid: %s\trssi: %d", i, apInfo[i].ssid, apInfo[i].rssi);
    //     sendUartStringNewLine(wifiBuffer);
    // }
    for (int i = 0; (i < 10) && (i < apCount); i++) {
        ESP_LOGI(TAG, "SSID \t\t%s", apInfo[i].ssid);
        ESP_LOGI(TAG, "RSSI \t\t%d", apInfo[i].rssi);
        // print_auth_mode(apInfo[i].authmode);
        if (apInfo[i].authmode != WIFI_AUTH_WEP) {
            // print_cipher_type(apInfo[i].pairwise_cipher, apInfo[i].group_cipher);
        }
        ESP_LOGI(TAG, "Channel \t\t%d\n", apInfo[i].primary);
    }
}

void staStopWifi() {
    esp_wifi_stop();
}

void staDeInitWifi() {
    esp_wifi_deinit();
}