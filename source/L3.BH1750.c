#include <L3.h>

//------------------------------------------------------------------------
// Inicializa I2C para BH1750
// Parametro: baud_rate
// Devuelve: nada
//------------------------------------------------------------------------
void BH1750_I2C(uint32_t baud_rate){
    /* Enables clock for switch matrix.: enable */
    CLOCK_Select(kI2C1_Clk_From_MainClk);
    CLOCK_EnableClock(kCLOCK_Swm);
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SDA, kSWM_PortPin_P0_27);
    SWM_SetMovablePinSelect(SWM0, kSWM_I2C1_SCL, kSWM_PortPin_P0_26);
    CLOCK_DisableClock(kCLOCK_Swm);
    i2c_master_config_t masterConfig;
    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = baud_rate;
    I2C_MasterInit(BH1750_I2C_BASE, &masterConfig, (12000000));

    BH1750_mode(BH1750_POWER_ON);
    BH1750_mode(BH1750_CONT_H_RES_MODE);
}
//------------------------------------------------------------------------

//------------------------------------------------------------------------
// Modo de funcionamiento BH1750
// Parametro: mode
// Devuelve: 0 = BH1750_OK, -1 = BH1750_ERROR
//------------------------------------------------------------------------
int8_t BH1750_mode(uint8_t mode){
	int32_t r;
	uint8_t x[5];
	x[0] = mode;
	if (kStatus_Success == I2C_MasterStart(BH1750_I2C_BASE, BH1750_ADDRESS, kI2C_Write))
    {
        r = I2C_MasterWriteBlocking(BH1750_I2C_BASE, x, 1, 0);
        if (r != kStatus_Success) return BH1750_ERROR;
        r = I2C_MasterStop(BH1750_I2C_BASE);
        if (r != kStatus_Success) return BH1750_ERROR;
    	return BH1750_OK;
    }
    else return BH1750_ERROR;
}
//------------------------------------------------------------------------
//------------------------------------------------------------------------
// Lectura de valor
// Parametro: mode y mtreg
// Devuelve: valor en lux con factor de conversion o BH1750_ERROR
//------------------------------------------------------------------------
float BH1750_ReadLight(uint8_t mode, uint8_t mtreg){
	int32_t r;
    if (kStatus_Success == I2C_MasterRepeatedStart(BH1750_I2C_BASE, BH1750_ADDRESS, kI2C_Read))
    {
    	uint8_t x[5];
        r = I2C_MasterReadBlocking(BH1750_I2C_BASE, x, 2, 0);
        if (r != kStatus_Success){ return BH1750_ERROR;}

        r = I2C_MasterStop(BH1750_I2C_BASE);
        if (r != kStatus_Success){ return BH1750_ERROR;}

        r = x[0]*256 + x[1];			// value read BH1750
        if (mode == BH1750_CONT_H_RES_MODE2 || mode == BH1750_ONE_TIME_H_RES_MODE2) {
            r /= 2;
        }
        float level = r;
        if (mtreg != BH1750_DEFAULT_MTREG) {
        	level *= (float)(BH1750_DEFAULT_MTREG/(float)mtreg);
        }
        level /= BH1750_CONV_FACTOR;			// Convert raw value to lux
        return level;
    }
    else return BH1750_ERROR;
}
//------------------------------------------------------------------------
