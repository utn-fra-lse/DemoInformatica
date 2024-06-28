#include <L2.h>
// UART1
usart_handle_t g_usartHandle1;
usart_transfer_t send_usart1, receive_usart1;

// UART0 debe inhabilitar la consola
usart_handle_t g_usartHandle0;
usart_transfer_t send_usart0, receive_usart0;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Inicializa UART1
//------------------------------------------------------------------------------------------------------
void UART1_Init(uint32_t baudRate, uint8_t *buff_rx, uint8_t buff_rx_size){
	CLOCK_Select(kUART1_Clk_From_MainClk);
	CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_USART1_TXD, kSWM_PortPin_P0_30);	    // USART0_TXD connect to P0_30
    SWM_SetMovablePinSelect(SWM0, kSWM_USART1_RXD, kSWM_PortPin_P0_31);		// USART0_RXD connect to P0_31
    CLOCK_DisableClock(kCLOCK_Swm);
    /* Default config by using USART_GetDefaultConfig():
     * config->baudRate_Bps = 9600U;
     * config->parityMode = kUSART_ParityDisabled;
     * config->stopBitCount = kUSART_OneStopBit;
     * config->bitCountPerChar = kUSART_8BitsPerChar;
     * config->loopback = false;
     * config->enableRx = false;
     * config->enableTx = false;
     * config->syncMode = kUSART_SyncModeDisabled;
     */

    usart_config_t user_config;
    USART_GetDefaultConfig(&user_config);
    user_config.baudRate_Bps = baudRate;
    user_config.enableTx = true;
    user_config.enableRx = true;
    USART_Init(USART1, &user_config, CLOCK_GetFreq(kCLOCK_MainClk));
    USART_TransferCreateHandle(USART1, &g_usartHandle1, USART1_UserCallback, NULL);

    receive_usart1.data = buff_rx;    		// Prepare to receive.
    receive_usart1.dataSize = buff_rx_size;
    USART_TransferReceiveNonBlocking(USART1, &g_usartHandle1, &receive_usart1, NULL);     // Receive.
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Envia datos por UART
//------------------------------------------------------------------------------------------------------
void UART1_Write(uint8_t *dat, uint16_t cant){
	send_usart1.data = dat;    				// Prepare to transmit.
	send_usart1.dataSize = cant;
	USART_TransferSendNonBlocking(USART1, &g_usartHandle1, &send_usart1);   // Send out.
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Lee datos por UART
//------------------------------------------------------------------------------------------------------
uint32_t UART1_Read(void){
	uint32_t count;
	USART_TransferGetReceiveCount(USART1,&g_usartHandle1, &count);
	if (count > 0)
    {
		USART_TransferAbortReceive(	USART1, &g_usartHandle1);
		USART_TransferReceiveNonBlocking(USART1, &g_usartHandle1, &receive_usart1, NULL);     // Receive.
    }
	return count;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void USART1_UserCallback(usart_handle_t *handle, status_t status, void *userData)
{
    userData = userData;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Inicializa UART0
//------------------------------------------------------------------------------------------------------
void UART0_Init(uint32_t baudRate, uint8_t *buff_rx, uint8_t buff_rx_size){
	CLOCK_Select(kUART0_Clk_From_MainClk);
	CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P0_25);		// USART0_TXD connect to P0_25
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P0_24);		// USART0_RXD connect to P0_24
    CLOCK_DisableClock(kCLOCK_Swm);
    /* Default config by using USART_GetDefaultConfig():
     * config->baudRate_Bps = 9600U;
     * config->parityMode = kUSART_ParityDisabled;
     * config->stopBitCount = kUSART_OneStopBit;
     * config->bitCountPerChar = kUSART_8BitsPerChar;
     * config->loopback = false;
     * config->enableRx = false;
     * config->enableTx = false;
     * config->syncMode = kUSART_SyncModeDisabled;
     */

    usart_config_t user_config;
    USART_GetDefaultConfig(&user_config);
    user_config.baudRate_Bps = baudRate;
    user_config.enableTx = true;
    user_config.enableRx = true;
    USART_Init(USART0, &user_config, CLOCK_GetFreq(kCLOCK_MainClk));
    USART_TransferCreateHandle(USART0, &g_usartHandle0, USART0_UserCallback, NULL);

    receive_usart0.data = buff_rx;    		// Prepare to receive.
    receive_usart0.dataSize = buff_rx_size;
    USART_TransferReceiveNonBlocking(USART0, &g_usartHandle0, &receive_usart0, NULL);     // Receive.
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Envia datos por UART
//------------------------------------------------------------------------------------------------------
void UART0_Write(uint8_t *dat, uint16_t cant){
	send_usart0.data = dat;    				// Prepare to transmit.
	send_usart0.dataSize = cant;
	USART_TransferSendNonBlocking(USART0, &g_usartHandle0, &send_usart0);   // Send out.
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Lee datos por UART
//------------------------------------------------------------------------------------------------------
uint32_t UART0_Read(void){
	uint32_t count;
	USART_TransferGetReceiveCount(USART0,&g_usartHandle0, &count);
	if (count > 0)
    {
		USART_TransferAbortReceive(	USART0, &g_usartHandle0);
		USART_TransferReceiveNonBlocking(USART0, &g_usartHandle0, &receive_usart0, NULL);     // Receive.
    }
	return count;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void USART0_UserCallback(usart_handle_t *handle, status_t status, void *userData)
{
    userData = userData;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
