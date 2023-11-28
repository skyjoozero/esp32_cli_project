#include "MySPI.h"

spi_host_device_t hostID;
spi_bus_config_t busConfig = { 
    .miso_io_num=-2,
    .mosi_io_num=-2,
    .sclk_io_num=-2,
    .quadwp_io_num=-2,
    .quadhd_io_num=-2,
    .max_transfer_sz=4091
};

spi_dma_chan_t dmaChan;

spi_device_interface_config_t spiDeviceInterfaceCon = {
        .clock_speed_hz = 5 * 1000 * 1000,
        .mode = 0,
        
    };
spi_device_handle_t spiDeviceHandle;

void initSPIBus(void) {
    hostID = SPI3_HOST;
    dmaChan = SPI_DMA_CH_AUTO;
    spi_bus_initialize(hostID, &busConfig, dmaChan);
}

void deInitSPIBUS(void) {
    spi_bus_free(hostID);
}