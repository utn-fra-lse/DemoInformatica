#include <L1.h>

void PWM_Init(void);
void PWM_Start(uint32_t freq, uint32_t duty2, uint32_t duty4);
void PWM_Stop(void);
void PWM_UpdateDuty_Out2(uint8_t dc);
void PWM_UpdateDuty_Out4(uint8_t dc);
