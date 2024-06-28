#include <L2.h>

enum { ADC0_CH0, ADC0_CH1, ADC0_CH2, ADC0_CH3, ADC0_CH4, ADC0_CH5, ADC0_CH6, ADC0_CH7, ADC0_CH8, ADC0_CH9, ADC0_CH10, ADC0_CH11};

volatile static uint16_t actives_channels;
uint16_t *adc_data_buffer, adc_data_valid;

void ADC0_Init(uint16_t channels, uint16_t *padc){
    uint32_t freq;
    adc_data_buffer = padc;
    actives_channels = channels;
	CLOCK_EnableClock(kCLOCK_Swm);
    if((channels & (1 << ADC0_CH0))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
    if((channels & (1 << ADC0_CH1))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN1, true);
    if((channels & (1 << ADC0_CH2))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN2, true);
    if((channels & (1 << ADC0_CH3))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN3, true);
    if((channels & (1 << ADC0_CH4))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN4, true);
    if((channels & (1 << ADC0_CH5))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN5, true);
    if((channels & (1 << ADC0_CH6))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN6, true);
    if((channels & (1 << ADC0_CH7))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN7, true);
    if((channels & (1 << ADC0_CH8))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN8, true);
    if((channels & (1 << ADC0_CH9))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN9, true);
    if((channels & (1 << ADC0_CH10))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN10, true);
    if((channels & (1 << ADC0_CH11))!=FALSE) SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN11, true);
    CLOCK_DisableClock(kCLOCK_Swm);

    CLOCK_Select(kADC_Clk_From_Fro);
    CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1U);
    POWER_DisablePD(kPDRUNCFG_PD_ADC0);

    freq = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
    (void) ADC_DoSelfCalibration(ADC0, freq);
    ADC_Configuration(channels);

    ADC_EnableInterrupts(ADC0, kADC_ConvSeqAInterruptEnable);
    NVIC_EnableIRQ(ADC0_SEQA_IRQn);
    ADC_DoSoftwareTriggerConvSeqA(ADC0);
}
//---------------------------------------------------------------//
void ADC_Configuration(uint16_t chs)
{
    adc_config_t adcConfigStruct;
    adc_conv_seq_config_t adcConvSeqConfigStruct;
    adcConfigStruct.clockMode = kADC_ClockSynchronousMode;
    adcConfigStruct.clockDividerNumber = 1;
    adcConfigStruct.enableLowPowerMode = false;
    adcConfigStruct.voltageRange = kADC_HighVoltageRange;
    ADC_Init(ADC0, &adcConfigStruct);
    /* Enable channel conversion in Sequence A. */
    adcConvSeqConfigStruct.channelMask = chs; /* Includes channel all channels to use. */
    adcConvSeqConfigStruct.triggerMask = 0;
    adcConvSeqConfigStruct.triggerPolarity = kADC_TriggerPolarityPositiveEdge;
    adcConvSeqConfigStruct.enableSingleStep = false;
    adcConvSeqConfigStruct.enableSyncBypass = false;
    adcConvSeqConfigStruct.interruptMode = kADC_InterruptForEachSequence;
    ADC_SetConvSeqAConfig(ADC0, &adcConvSeqConfigStruct);
    ADC_EnableConvSeqA(ADC0, true); /* Enable the conversion sequence A. */
    ADC_DoSoftwareTriggerConvSeqA(ADC0);
}
//---------------------------------------------------------------//
void ADC_Read_Data(uint16_t *p){
	adc_result_info_t AdcInfoStruct;
	uint8_t i;
	for(i=0;i<=ADC0_CH11;i++){
		if((actives_channels & (1 << i))!=FALSE){
			ADC_GetChannelConversionResult(ADC0, i, &AdcInfoStruct);
			*p = AdcInfoStruct.result;
		}
		p++;
	}
}
//---------------------------------------------------------------//
void ADC_Clear_Flags(void){
	ADC_ClearStatusFlags(ADC0, kADC_ConvSeqAInterruptFlag);
}
//---------------------------------------------------------------//
uint8_t ADC_End_Conversion(void){
	if (kADC_ConvSeqAInterruptFlag == (kADC_ConvSeqAInterruptFlag & ADC_GetStatusFlags(ADC0)))
    {
		return TRUE;
	} else{
		return FALSE;
	}
}
//---------------------------------------------------------------//
void ADC0_SEQA_IRQHandler(void)
{
    if (ADC_End_Conversion()==TRUE)
    {
        ADC_Read_Data(adc_data_buffer);
        ADC_Clear_Flags();
        adc_data_valid = TRUE;
    }
}
//---------------------------------------------------------------//
