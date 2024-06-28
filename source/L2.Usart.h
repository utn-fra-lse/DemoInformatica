#include <L1.h>

#define SIZE_BUFFER 64

void UART1_Init(uint32_t baudRate, uint8_t *buff_rx, uint8_t buff_rx_size);
void UART1_Write(uint8_t *dat, uint16_t cant);
uint32_t UART1_Read(void);
void USART1_UserCallback(usart_handle_t *handle, status_t status, void *userData);

void UART0_Init(uint32_t baudRate, uint8_t *buff_rx, uint8_t buff_rx_size);
void UART0_Write(uint8_t *dat, uint16_t cant);
uint32_t UART0_Read(void);
void USART0_UserCallback(usart_handle_t *handle, status_t status, void *userData);
