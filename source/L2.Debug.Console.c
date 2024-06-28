#include <L2.h>

//const unsigned int ExtClockIn = EXTCLKINRATE;					// Clock rate on the CLKIN pin

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Inicializa DebugConsole
//------------------------------------------------------------------------------------------------------
int DebugConsole_Init(void){
    CLOCK_Select(kUART0_Clk_From_MainClk);
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_TXD, kSWM_PortPin_P0_25);		// USART0_TXD connect to P0_25
    SWM_SetMovablePinSelect(SWM0, kSWM_USART0_RXD, kSWM_PortPin_P0_24);		// USART0_RXD connect to P0_24
    CLOCK_DisableClock(kCLOCK_Swm);

    int result;
    /* Select the main clock as source clock of USART0 (debug console) */
    CLOCK_Select(DEBUG_USART_CLK_ATTACH);
    RESET_PeripheralReset(DEBUG_USART_RST);
    result = DbgConsole_Init(DEBUG_USART_INSTANCE, DEBUG_USART_BAUDRATE, DEBUG_USART_TYPE, DEBUG_USART_CLK_FREQ);
    assert(kStatus_Success == result);
    return result;
}
//------------------------------------------------------------------------------------------------------
