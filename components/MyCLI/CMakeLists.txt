idf_component_register(SRCS "MyCLI.c"
                    INCLUDE_DIRS "include"
                    REQUIRES MyUart MyGPIO MyWIFI MyGPSModule)
