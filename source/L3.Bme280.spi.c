#include <L3.h>

int16_t  BME280_Temp=0, BME280_Press=0, BME280_Hum=0;
static struct bme280_dev dev;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void BME280_Init(uint32_t baud_rate){
	CS0_SPI_ENABLE;
	Delay_mseg(1);
	CS0_SPI_DISABLE;
    SPI_Init(baud_rate);

	int8_t rslt = BME280_OK;

    /* Sensor_0 interface over SPI with native chip select line */
    dev.dev_id = 0;
    dev.intf = BME280_SPI_INTF;
    dev.read = user_spi_read_write;
    dev.write = user_spi_read_write;
    dev.delay_ms = user_delay_ms;

    rslt = bme280_init(&dev);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void BME280_Data_Forced(void){
	(void) stream_sensor_data_forced_mode(&dev);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void BME280_Data_Normal(void){
	(void) stream_sensor_data_normal_mode(&dev);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void user_delay_ms(uint32_t period)
{
	Delay_mseg(period);
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int8_t user_spi_read_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
	uint8_t datax;
	CS0_SPI_ENABLE;
	SPI_Write_Read(&reg_addr, &datax, 1);
	datax++;
	SPI_Write_Read(data, data, len);
	CS0_SPI_DISABLE;
    return BME280_OK;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
void print_sensor_data(struct bme280_data *comp_data)
{
    float temp, press, hum;
#ifdef BME280_FLOAT_ENABLE
    temp = comp_data->temperature;
    press = 0.01 * comp_data->pressure;
    hum = comp_data->humidity;
#else
#ifdef BME280_64BIT_ENABLE
    temp = 0.01f * comp_data->temperature;
    press = 0.0001f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#else
    temp = 0.01f * comp_data->temperature;
    press = 0.01f * comp_data->pressure;
    hum = 1.0f / 1024.0f * comp_data->humidity;
#endif
#endif
    //PRINTF("%d deg C, %d hPa, %0d%%\n", (int16_t)temp, (int16_t)press, (int16_t)hum);
    BME280_Temp = (int16_t)temp;
    BME280_Press = (int16_t)press;
    BME280_Hum = (int16_t)hum;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev)
{
    int8_t rslt;
    uint8_t settings_sel;
    struct bme280_data comp_data;

    /* Recommended mode of operation: Indoor navigation */
    dev->settings.osr_h = BME280_OVERSAMPLING_1X;
    dev->settings.osr_p = BME280_OVERSAMPLING_16X;
    dev->settings.osr_t = BME280_OVERSAMPLING_2X;
    dev->settings.filter = BME280_FILTER_COEFF_16;

    settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    rslt = bme280_set_sensor_settings(settings_sel, dev);
    if (rslt != BME280_OK)
    {
        //PRINTF("Failed to set sensor settings (code %+d).", rslt);
        return rslt;
    }
    //while (1)
    //{
        rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, dev);
        if (rslt != BME280_OK)
        {
         	//PRINTF("Failed to set sensor mode (code %+d).", rslt);
            return rslt;
        }
        /* Wait for the measurement to complete and print data @25Hz */
        dev->delay_ms(40);
        rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
        if (rslt != BME280_OK)
        {
         	//PRINTF("Failed to get sensor data (code %+d).", rslt);
            return rslt;
        }
        print_sensor_data(&comp_data);
        dev->delay_ms(1000);
    //}
    return rslt;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	//printf("Temperature, Pressure, Humidity\r\n");
	//while (1) {
		/* Delay while the sensor completes a measurement */
		dev->delay_ms(70);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	//}

	return rslt;
}
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
