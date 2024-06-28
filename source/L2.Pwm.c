#include <L2.h>

sctimer_config_t sctimerInfo;
uint32_t sctimerClock;
sctimer_pwm_signal_param_t pwmParam1, pwmParam2, pwmParam3, pwmParam4;
uint32_t event;

//------------------------------------------------------------------------
// Inicializa PWM out2 y out4
// Parametro: ninguno
// Devuelve: ninguno
//------------------------------------------------------------------------
void PWM_Init(void){
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT4, kSWM_PortPin_P1_1);
    SWM_SetMovablePinSelect(SWM0, kSWM_SCT_OUT2, kSWM_PortPin_P0_29);
    CLOCK_DisableClock(kCLOCK_Swm);


    sctimerClock = CLOCK_GetFreq(kCLOCK_Fro);
    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Inicia PWM out2 y out4
// Parametro: frecuencia, ciclo actividad out2, ciclo actividad out4,
// Devuelve: ninguno
//------------------------------------------------------------------------
void PWM_Start(uint32_t freq, uint32_t duty2, uint32_t duty4){
    pwmParam4.output           = kSCTIMER_Out_4;
    pwmParam4.level            = kSCTIMER_HighTrue;
    pwmParam4.dutyCyclePercent = duty4;

    pwmParam2.output           = kSCTIMER_Out_2;
    pwmParam2.level            = kSCTIMER_HighTrue;
    pwmParam2.dutyCyclePercent = duty2;

    SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_L);
    SCTIMER_Init(SCT0, &sctimerInfo);
    SCTIMER_SetupPwm(SCT0, &pwmParam4, kSCTIMER_EdgeAlignedPwm, freq, sctimerClock, &event);
    SCTIMER_SetupPwm(SCT0, &pwmParam2, kSCTIMER_EdgeAlignedPwm, freq, sctimerClock, &event);
    SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_L);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Detiene PWM out2 y out4
// Parametro: ninguno
// Devuelve: ninguno
//------------------------------------------------------------------------
void PWM_Stop(void){
    SCTIMER_StopTimer(SCT0, kSCTIMER_Counter_L);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Actualiza duty cycle PWM out2
// Parametro: dc
// Devuelve: ninguno
//------------------------------------------------------------------------
void PWM_UpdateDuty_Out2(uint8_t dc){
	SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_2 , dc, event);
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Actualiza duty cycle PWM out4
// Parametro: dc
// Devuelve: ninguno
//------------------------------------------------------------------------
void PWM_UpdateDuty_Out4(uint8_t dc){
	SCTIMER_UpdatePwmDutycycle(SCT0, kSCTIMER_Out_4 , dc, event);
}
//------------------------------------------------------------------------
