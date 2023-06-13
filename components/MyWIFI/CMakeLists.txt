idf_component_register(SRCS "MyWIFI.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_wifi nvs_flash log MyUart)
