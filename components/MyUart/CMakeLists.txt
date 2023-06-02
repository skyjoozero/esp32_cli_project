idf_component_register(SRCS "MyUart.c"
                    INCLUDE_DIRS "include"
                    REQUIRES driver soc freertos hal Util)
