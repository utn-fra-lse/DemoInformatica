// defines BH1750
#include <L2.h>

#define BH1750_OK 					0
#define BH1750_ERROR 				-1

#define BH1750_I2C_BASE 			((I2C_Type *)(I2C1_BASE))//
#define BH1750_ADDRESS	 			0x5C	// Address BH1750
#define BH1750_POWER_DOWN 			0x00	// No active state
#define BH1750_POWER_ON 			0x01	// Waiting for measurement command
#define BH1750_RESET 				0x07	// Reset data register value - not accepted in POWER_DOWN mode
#define BH1750_CONT_H_RES_MODE  	0x10	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
#define BH1750_CONT_H_RES_MODE2 	0x11    // Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
#define BH1750_CONT_L_RES_MODE  	0x13	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
#define BH1750_ONE_TIME_H_RES_MODE 	0x20	// Measurement at 1 lux resolution. Measurement time is approx 120ms.
#define BH1750_ONE_TIME_H_RES_MODE2 0x21	// Measurement at 0.5 lux resolution. Measurement time is approx 120ms.
#define BH1750_ONE_TIME_L_RES_MODE  0x23	// Measurement at 4 lux resolution. Measurement time is approx 16ms.
#define BH1750_DEFAULT_MTREG 		69		// Default MTreg value typical light environment (lux > 10)
#define BH1750_LOW_MTREG 			138		// very low light environment (lux < 10)
#define BH1750_FULL_MTREG 			132		// reduce measurement time - needed in direct sun light (lux > 40000)
#define BH1750_CONV_FACTOR 			1.2		// Correction factor used to calculate lux. Typical value is 1.2 but can range from 0.96 to 1.44. See the data sheet (p.2, Measurement Accuracy)

void BH1750_I2C(uint32_t baud_rate);
int8_t BH1750_mode(uint8_t mode);
float BH1750_ReadLight(uint8_t mode, uint8_t mtreg);
