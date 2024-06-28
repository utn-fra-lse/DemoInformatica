#include <L1.h>


extern uint16_t *adc_data_buffer, adc_data_valid;

void ADC0_Init(uint16_t channels, uint16_t *padc);
void ADC_Configuration(uint16_t chs);
void ADC_Read_Data(uint16_t *p);
void ADC_Clear_Flags(void);
uint8_t ADC_End_Conversion(void);
