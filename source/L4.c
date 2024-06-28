#include <L2.h>
#include <L3.h>
#include <L4.h>
#include <stdarg.h>
#include <stdio.h>

uint16_t adc_ch[12];
uint8_t lcd_switch = REFRESH_7SEG, new_refresh = REFRESH_7SEG, up_no_down = 0;
uint8_t	dig[3]="00", digitos_7seg = 0, dig_on = DIGIT_1;
uint8_t	buffer_txd[BUFFER_UART_TX_SIZE], buffer_rxd0[BUFFER_UART_RX_SIZE], buffer_rxd1[BUFFER_UART_RX_SIZE];
//------------------------------------------------------------------------------------------------------
void ctimer_match0_interrupt(void){
}
//------------------------------------------------------------------------------------------------------
/*!
 * Initializa modulos del kit
 * Parametro: debugConsoleEnable = 0, habilita el uso de consola
 * Parametro: debugConsoleEnable != 0, habilita el Usart0 para uso por uUSB
 */
void Kit_Cortex_Init(){
	ClockFRO30M();
	GPIO_Init();
	#if CONSOLE_LOCAL == 0
		DebugConsole_Init();
	#else
		UART0_Init(BAUD_RATE_UART, buffer_rxd0, BUFFER_UART_RX_SIZE);	// PC
	#endif
	SysTick_Init(TICK_1ms_30M);
	BME280_Init(BAUD_RATE_SPI);
	BH1750_I2C(BAUD_RATE_I2C);
	//UART1_Init(BAUD_RATE_UART, buffer_rxd1, BUFFER_UART_RX_SIZE);	// MOBILE

	ADC0_Init(ADC_R21 | ADC_R22 , &adc_ch[0]);
	//DAC1_Init();
	//DAC1_Write(0);
}
//------------------------------------------------------------------------------------------------------
/*!
 * incremento de 1mseg por interrupcion
 */
void Tick_1mseg_interrupt(void){
	// display 7 segmentos
	if(lcd_switch!=0) lcd_switch--;
	else{
		lcd_switch = new_refresh;
		if(dig_on != DIGIT_1){
			dig_on = DIGIT_1;
			Write_7segment(dig[0]-0x30,1,dig_on);
		}
		else{
			dig_on = DIGIT_2;
			Write_7segment(dig[1]-0x30,1,dig_on);
		}
	}
}
//------------------------------------------------------------------------------------------------------
/*!
 * Enciende led seleccionado
 * parametros: BLUE, GREEN, RED o WBLUE 
 */
void Led_On(uint8_t led){
	switch (led)
	{
		case BLUE:
			BLUE_LED_ON; RED_LED_OFF; GREEN_LED_OFF;
			break;
		case GREEN:
			GREEN_LED_ON; RED_LED_OFF; BLUE_LED_OFF;
			break;
		case RED:
			RED_LED_ON; GREEN_LED_OFF; BLUE_LED_OFF;
			break;
		case WBLUE:
			WC_LED_ON; 
			break;
		default:
			WC_LED_OFF; BLUE_LED_OFF; 
			RED_LED_OFF; GREEN_LED_OFF;
			break;
	}
}
//------------------------------------------------------------------------------------------------------
/*!
 * Apaga led seleccionado
 * parametros: (uint8_t) BLUE, GREEN, RED o WBLUE 
 */
void Led_Off(uint8_t led){
	switch (led)
	{
		case BLUE:
			BLUE_LED_OFF;
			break;
		case GREEN:
			GREEN_LED_OFF;
			break;
		case RED:
			RED_LED_OFF;
			break;
		case WBLUE:
			WC_LED_OFF; 
			break;
		default:
			WC_LED_OFF; BLUE_LED_OFF; 
			RED_LED_OFF; GREEN_LED_OFF;
			break;
	}
}
//------------------------------------------------------------------------------------------------------
/*!
 * Genera demoras en milisegundos
 * parametros: (uint32_t) milisegundos 
 */
void Delay(uint32_t mseg){
	Delay_mseg(mseg);
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene valor analogico de R21
 * retorno: (uint16_t) valor analogico
 */
uint16_t Get_R21(void){
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
	while(adc_data_valid == FALSE);
   	adc_data_valid = FALSE;
	return adc_ch[0];
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene valor analogico de R22
 * retorno: (uint16_t) valor analogico
 */
uint16_t Get_R22(void){
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
	while(adc_data_valid == FALSE);
   	adc_data_valid = FALSE;
	return adc_ch[8];
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene temperatura
 * retorno: (uint16_t) temperatura en °C
 */
uint16_t Get_Temperature(void){
	BME280_Data_Normal();
	return BME280_Temp;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene humedad relativa
 * retorno: (uint16_t) humedad %
 */
uint16_t Get_Humidity(void){
	BME280_Data_Normal();
	return BME280_Hum;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene presion atmosferica
 * retorno: (uint16_t) presion en hPa
 */
uint16_t Get_Pressure(void){
	BME280_Data_Normal();
	return BME280_Press;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene intensidad luminica
 * retorno: (uint16_t) intensidad luminica en LUX
 */
uint16_t Get_Lux(void){
    uint16_t lux = BH1750_ReadLight(BH1750_CONT_H_RES_MODE, BH1750_DEFAULT_MTREG);
	return lux;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Escribe valor en display 7 segmentos de 2 digitos
 * parameto: (uint8_t) numero a mostrar
 */
void Display_Segments(uint8_t value){
	if(value > 99)
		return;

    (void)sprintf(dig,"%02d", value);
}
//------------------------------------------------------------------------------------------------------
/*!
 * Guarda informacion en memoria
 * parameto: (uint8_t *) mensaje
 * retorno: 0-FALSE si fallo, si no distinto de 0 (TRUE)
 */
uint8_t Save_Text(uint8_t *text){
	uint8_t buffer[MAX_BYTES];
	for(int i = 0; i < MAX_BYTES; i++){
		buffer[i] = *text;
		if(buffer[i] == NULL)
				break;
		text++;
	}
	if( IAP_PrepareSectorForWrite(SECTOR,SECTOR) != kStatus_IAP_Success){
    	return FALSE;
    }
    if(IAP_EraseSector(SECTOR,SECTOR,FREQ_30MHZ)!=kStatus_IAP_Success){
    	return FALSE;
    }
    if(IAP_PrepareSectorForWrite(SECTOR,SECTOR)!=kStatus_IAP_Success){
    	return FALSE;
    }
    status_t resp = IAP_CopyRamToFlash(FLASH_ADDRESS, &buffer[0], MAX_BYTES, FREQ_30MHZ);
    if(resp!=kStatus_IAP_Success){
    	return FALSE;
    }
	return TRUE;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Guarda informacion en memoria
 * parameto: (uint8_t *) mensaje
 */
void Get_Text_Saved(uint8_t *text){
	uint8_t *p;
	p = NULL;
	p += FLASH_ADDRESS;
	for(int i = 0; i < MAX_BYTES; i++){
		*text = *p;
		if(*p == NULL)
			break;
		text++;
		p++;
	}
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene estado de la tecla
 * retorno: (uint8_t) 0 tecla presionada, sino distinto de 0
 */
uint8_t Get_Key_S1(void){
	return SW_S1;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene estado de la tecla
 * retorno: (uint8_t) 0 tecla presionada, sino distinto de 0
 */
uint8_t Get_Key_S2(void){
	return SW_S2;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene estado de la tecla
 * retorno: (uint8_t) 0 tecla presionada, sino distinto de 0
 */
uint8_t Get_Key_USER(void){
	return SW_USER;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene estado de la tecla
 * retorno: (uint8_t) 0 tecla presionada, sino distinto de 0
 */
uint8_t Get_Key_ISP(void){
	return SW_ISP;
}
//------------------------------------------------------------------------------------------------------
/*!
 * Obtiene estado de la salida del CNY70
 * retorno: (uint8_t) 0 = sin objeto, 1 = objeto detectado
 */
uint8_t Get_CNY70(void){
	CNY70_ON;
	return CNY70_STATUS;
}
//------------------------------------------------------------------------------------------------------
void Console_Write(char console_uart, const char *format, ...){
	char buffer[30];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);

    va_end(args);
	if (console_uart == CONSOLE_ENABLE){
    	printf(buffer);
	}
	else{
    	int length = strlen(buffer);
    	UART0_Write(buffer, length);
    	Delay_mseg(100);
	}
}
//------------------------------------------------------------------------------------------------------

