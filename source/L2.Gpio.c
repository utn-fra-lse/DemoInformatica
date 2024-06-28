#include <L2.h>
							// 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   .
uint8_t tabla_7seg[12]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x10,0x7F};


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Inicializa GPIO
//------------------------------------------------------------------------------------------------------
void GPIO_Init(void){
    gpio_pin_config_t out_config = {kGPIO_DigitalOutput, 1};
    gpio_pin_config_t in_config = {kGPIO_DigitalInput};
    GPIO_PortInit(GPIO, 0);
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(GPIO, 1, 0, &out_config);			// GREEN_LED
    GPIO_PinInit(GPIO, 1, 1, &out_config);			// BLUE_LED
    GPIO_PinInit(GPIO, 1, 2, &out_config);			// RED_LED

    GPIO_PinInit(GPIO, 0, 0, &out_config);			// SEG_E - LCD_RS
    GPIO_PinInit(GPIO, 0, 1, &out_config);			// SEG_DOT - LCD_RW
//  GPIO_PinInit(GPIO, 0, 2, &out_config);			// SWDIO
//  GPIO_PinInit(GPIO, 0, 3, &out_config);			// SWCLK
    GPIO_PinInit(GPIO, 0, 4, &in_config);			// SW_USER
//  GPIO_PinInit(GPIO, 0, 5, &in_config);			// RESET
    GPIO_PinInit(GPIO, 0, 6, &out_config);			// SEG_C - LCD_E
    GPIO_PinInit(GPIO, 0, 7, &in_config);			// ADC7 preset
    GPIO_PinInit(GPIO, 0, 8, &out_config);			// DIGITO 2
    GPIO_PinInit(GPIO, 0, 9, &out_config);			// DIGITO 1
    GPIO_PinInit(GPIO, 0, 10, &out_config);			// SEG_A - LCD_BL
    GPIO_PinInit(GPIO, 0, 11, &out_config);			// SEG_B - LCD_DB7
    GPIO_PinInit(GPIO, 0, 12, &in_config);			// SW_ISP
    GPIO_PinInit(GPIO, 0, 13, &out_config);			// SEG_F - LCD_DB6
    GPIO_PinInit(GPIO, 0, 14, &out_config);			// SEG_D - LCD_DB5
    GPIO_PinInit(GPIO, 0, 15, &out_config);			// SEG_G - LCD_DB4
    GPIO_PinInit(GPIO, 0, 16, &in_config);			// SW_S1
    GPIO_PinInit(GPIO, 0, 17, &out_config);			// DAC1-CNY70_ON
    GPIO_PinInit(GPIO, 0, 18, &in_config);			// ADC8 preset
    GPIO_PinInit(GPIO, 0, 19, &in_config);			// ADC0 LM335 - CNY70_data
    GPIO_PinInit(GPIO, 0, 20, &out_config);			// SPI0 MISO
    GPIO_PinInit(GPIO, 0, 21, &out_config);			// SPI0 CS
    GPIO_PinInit(GPIO, 0, 22, &in_config);			// SPI0	MOSI
    GPIO_PinInit(GPIO, 0, 23, &out_config);			// SPI0 CLK
    GPIO_PinInit(GPIO, 0, 24, &in_config);			// UART0
    GPIO_PinInit(GPIO, 0, 25, &out_config);			// UART0 - SW_S2
    GPIO_PinInit(GPIO, 0, 26, &out_config);			// IIC1_SCL
    GPIO_PinInit(GPIO, 0, 27, &out_config);			// IIC1_SDA
    GPIO_PinInit(GPIO, 0, 28, &out_config);			// BUZZER
    GPIO_PinInit(GPIO, 0, 29, &out_config);			// DAC0 - LED_WC
    GPIO_PinInit(GPIO, 0, 30, &out_config);			// UART1_RXD
    GPIO_PinInit(GPIO, 0, 31, &out_config);			// UART1_TXD
    //GPIO_PinWrite(GPIO, 0, 21, 0);
    GPIO_PinWrite(GPIO, 0, 28, 0);
}
//------------------------------------------------------------------------------------------------------
void Write_7segment(uint8_t num, uint8_t dp, uint8_t digit){
	union {
		uint8_t segments;
		struct{
			uint8_t a:1;
			uint8_t b:1;
			uint8_t c:1;
			uint8_t d:1;
			uint8_t e:1;
			uint8_t f:1;
			uint8_t g:1;
			uint8_t dp:1;
		} segment;
	} lcd;
	lcd.segments = tabla_7seg[num];
	lcd.segment.dp = dp;
	SEG_A(lcd.segment.a);
	SEG_B(lcd.segment.b);
	SEG_C(lcd.segment.c);
	SEG_D(lcd.segment.d);
	SEG_E(lcd.segment.e);
	SEG_F(lcd.segment.f);
	SEG_G(lcd.segment.g);
	SEG_DOT(lcd.segment.dp);

	if(digit == 1){
		DIGIT_1_ON;
		DIGIT_2_OFF;
	}
	if(digit == 2){
		DIGIT_2_ON;
		DIGIT_1_OFF;
	}
}
//------------------------------------------------------------------------------------------------------
