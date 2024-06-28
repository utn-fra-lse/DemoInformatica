#include <L1.h>

#define EXTCLKINRATE (0)

// @brief The UART to use for debug messages.
#define DEBUG_USART_TYPE kSerialPort_Uart
#define DEBUG_USART_BASEADDR (uint32_t) USART0
#define DEBUG_USART_INSTANCE 0U
#define DEBUG_USART_CLK_FREQ CLOCK_GetMainClkFreq()
#define DEBUG_USART_CLK_ATTACH kUART0_Clk_From_MainClk
#define DEBUG_USART_RST kUART0_RST_N_SHIFT_RSTn
#define UART_IRQ USART0_IRQn
#define UART_IRQ_HANDLER USART0_IRQHandler
#define DEBUG_USART_BAUDRATE 9600

int DebugConsole_Init(void);
