#include <L1.h>

void PWM_Init(uint8_t selector);
void PWM_Init24(void);
void PWM_Start(uint32_t freq, uint8_t duty2);
void PWM_Start24(uint32_t freq, uint8_t duty2, uint8_t duty4);
void PWM_Stop(void);
void PWM_DeInit(void);
void PWM_UpdateDuty_Out2(uint8_t dc);
void PWM_UpdateDuty_Out4(uint8_t dc);
