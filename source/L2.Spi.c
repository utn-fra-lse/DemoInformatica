#include <L2.h>
//------------------------------------------------------------------------------------------------------
unsigned long br;
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// ReInicializa SPI
//------------------------------------------------------------------------------------------------------
void SPI_ReInit(unsigned long bRate){
    spi_master_config_t userConfig = {0};
    uint32_t srcFreq               = 0U;
    /* Note: The slave board using interrupt way, slave will spend more time to write data
     *       to TX register, to prevent TX data missing in slave, we will add some delay between
     *       frames and capture data at the second edge, this operation will make the slave
     *       has more time to prapare the data.
     */
    SPI_MasterGetDefaultConfig(&userConfig);
    userConfig.baudRate_Bps           = bRate;
    userConfig.sselNumber             = kSPI_SselDeAssertAll;//kSPI_Ssel0Assert;
    userConfig.clockPolarity		  = kSPI_ClockPolarityActiveHigh;
    userConfig.clockPhase             = kSPI_ClockPhaseFirstEdge;
    userConfig.delayConfig.frameDelay = 0x0U;
    srcFreq                           = CLOCK_GetFreq(kCLOCK_MainClk);
    SPI_MasterInit(SPI0, &userConfig, srcFreq);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Inicializa SPI
//------------------------------------------------------------------------------------------------------
void SPI_Init(unsigned long baudRate){
    br = baudRate;
	CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_SPI0_SCK, kSWM_PortPin_P0_23);	// SPI0_SCK connect to P0_23
    SWM_SetMovablePinSelect(SWM0, kSWM_SPI0_MOSI, kSWM_PortPin_P0_22);	// SPI0_MOSI connect to P0_22
    SWM_SetMovablePinSelect(SWM0, kSWM_SPI0_MISO, kSWM_PortPin_P0_20);	// SPI0_MISO connect to P0_20
    //SWM_SetMovablePinSelect(SWM0, kSWM_SPI0_SSEL0, kSWM_PortPin_P0_21);	// SPI0_SSEL0 connect to P0_21
    CLOCK_DisableClock(kCLOCK_Swm);										// Disable clock for switch matrix.
    CLOCK_Select(kSPI0_Clk_From_MainClk);
    SPI_ReInit(br);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Escribe y lee por SPI
//------------------------------------------------------------------------------------------------------
void SPI_Write_Read(unsigned char *txd, unsigned char *rxd, unsigned char cant){
    spi_transfer_t xfer = {0};
    xfer.txData      = txd;
    xfer.rxData      = rxd;
    xfer.dataSize    = cant;
    xfer.configFlags = kSPI_EndOfTransfer | kSPI_EndOfFrame;
    //SPI_ReInit(br);
    SPI_MasterTransferBlocking(SPI0, &xfer);							// Transfer data in polling mode
    //SPI_Deinit(SPI0);													// De-initialize the SPI.
}
//------------------------------------------------------------------------------------------------------
