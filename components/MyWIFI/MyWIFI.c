#include "MyWIFI.h"

uint16_t number = DEFAULT_SCAN_LIST_SIZE;
uint16_t apCount = 0;
char wifiBuffer[128];

// wifi_auth_mode_t wifi_auth_mode;
wifi_ap_record_t apInfo[MAX_WIFI_SEARCH];


void staInitWifi() {
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    memset(apInfo, 0, sizeof(apInfo));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void staScanWifi() {
    // staInitWifi();
    

    
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, apInfo));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&apCount));
}

static void print_auth_mode(int authmode) {

    switch (authmode) {
    case WIFI_AUTH_OPEN:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_OPEN\n");
        break;
    case WIFI_AUTH_OWE:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_OWE\n");
        break;
    case WIFI_AUTH_WEP:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WEP\n");
        break;
    case WIFI_AUTH_WPA_PSK:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA_PSK\n");
        break;
    case WIFI_AUTH_WPA2_PSK:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA2_PSK\n");
        break;
    case WIFI_AUTH_WPA_WPA2_PSK:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA_WPA2_PSK\n");
        break;
    case WIFI_AUTH_WPA2_ENTERPRISE:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA2_ENTERPRISE\n");
        break;
    case WIFI_AUTH_WPA3_PSK:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA3_PSK\n");
        break;
    case WIFI_AUTH_WPA2_WPA3_PSK:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_WPA2_WPA3_PSK\n");
        break;
    default:
        sendUartStrings(UART_NUM_1, 1, "Authmode \tWIFI_AUTH_UNKNOWN\n");
        break;
    }

}

static void print_cipher_type(int pairwise_cipher, int group_cipher) {

    switch (pairwise_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_NONE\n");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_WEP40\n");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_WEP104\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_TKIP\n");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_TKIP_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_AES_CMAC128:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_AES_CMAC128\n");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_SMS4\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_GCMP\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_GCMP256\n");
        break;
    default:
        sendUartStrings(UART_NUM_1, 1, "Pairwise Cipher WIFI_CIPHER_TYPE_UNKNOWN\n");
        break;
    }

    switch (group_cipher) {
    case WIFI_CIPHER_TYPE_NONE:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_NONE\n");
        break;
    case WIFI_CIPHER_TYPE_WEP40:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_WEP40\n");
        break;
    case WIFI_CIPHER_TYPE_WEP104:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_WEP104\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP\n");
        break;
    case WIFI_CIPHER_TYPE_CCMP:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_TKIP_CCMP:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_TKIP_CCMP\n");
        break;
    case WIFI_CIPHER_TYPE_SMS4:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_SMS4\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP\n");
        break;
    case WIFI_CIPHER_TYPE_GCMP256:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_GCMP256\n");
        break;
    default:
        sendUartStrings(UART_NUM_1, 1, "Group Cipher \tWIFI_CIPHER_TYPE_UNKNOWN\n");
        break;
    }
}

uint16_t staReturnScanedApNum() {
    return apCount;
}

void staShowScannedWifiList() {
    // sendUartString(1, "Total APs scanned = %u", ap_count);
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < apCount); i++) {
        sendUartStrings(UART_NUM_1, 3, "\nSSID \t\t", apInfo[i].ssid, "\n");
        // sendUartString(2, "RSSI \t\t%d", ap_info[i].rssi);
        print_auth_mode(apInfo[i].authmode);
        if (apInfo[i].authmode != WIFI_AUTH_WEP) {
            print_cipher_type(apInfo[i].pairwise_cipher, apInfo[i].group_cipher);
            
        }
        
        // sendUartString(1, "Channel \t\t%d", ap_info[i].primary);
    }
}

void staConnectWifi() {
    // sendUartString("(wifi) ssid ");
    // uint8_t *wifiSsid = (uint8_t *) receiveUartStringData();
    // sendUartString("(wifi) password ");
    // uint8_t *wifiPassword = (uint8_t *) receiveUartStringData();
    // wifi_auth_mode_t authMode = WIFI_AUTH_WPA2_PSK;
    wifi_config_t wifiConfig = {
        .sta = {
            .ssid = "iptime",
            .password = "a3986991!",
            .threshold.authmode = WIFI_AUTH_WPA2_PSK,
        },
    };
    // memcpy(wifiConfig.sta.ssid, wifiSsid, strlen(&wifiSsid));
    // memcpy(wifiConfig.sta.password, wifiPassword, strlen(&wifiPassword));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifiConfig));
    ESP_ERROR_CHECK(esp_wifi_connect());
}

void staDisconnectWifi() {
    ESP_ERROR_CHECK(esp_wifi_disconnect());
}

void staStopWifi() {
    ESP_ERROR_CHECK(esp_wifi_stop());
}

void staDeInitWifi() {
    ESP_ERROR_CHECK(esp_wifi_deinit());
}