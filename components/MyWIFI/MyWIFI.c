#include "MyWIFI.h"


void staInitWifi() {
    esp_wifi_init(WIFI_INIT_CONFIG_DEFAULT);
    esp_wifi_Set_mode(WIFI_MODE_STA);
}

void staRunWifi() {
    esp_wifi_start();
}

void staScanWifi() {
    wifi_scan_config_t scanConfig;
    scanConfig.show_hidden = true;
    scanConfig.scan_type = WIFI_SCAN_TYPE_ACTIVE;
    scanConfig.scan_time = 
    esp_wifi_scan_start();
}

void staStopWifi() {
    esp_wifi_stop();
}

void staDeInitWifi() {
    esp_wifi_deinit();
}