#include "MySPI.h"

spi_host_divice_t hostID;
spi_bus_config_t busConfig;
spi_dma_chan_t dmaChan;

spi_divice_interface_config_t spiDiviceInterfaceCon;
spi_divice_handle_t spiDiviceHandle;

void initSPIBus(void) {
    hostID = SPI3_HOST;
    busConfig = { 
        .miso_io_num=-1,
        .mosi_io_num=-1,
        .sclk_io_num=-1,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=4092
    };
    dmaChan = SPI_DMA_CH1;
    spi_bus_initialize(hostID, &busConfig, dmaChan)
}

void initSPIDiviceConfig(void) {
    initSPIDiviceConfig = {
        .clock_speed_hz = 5 * 1000 * 1000,
        .mode = 0,
        
    }
}

void deInitSPIBUS(void) {
    spi_bus_free(hostID);
}