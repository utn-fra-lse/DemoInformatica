#include <L2.h>

#define CS0_SPI_ENABLE		GPIO_PinWrite(GPIO, 0, 21, 0)
#define CS0_SPI_DISABLE		GPIO_PinWrite(GPIO, 0, 21, 1)

extern int16_t  BME280_Temp, BME280_Press, BME280_Hum;

void BME280_Init(uint32_t baud_rate);
void BME280_Data_Forced(void);
void BME280_Data_Normal(void);

int8_t user_spi_read_write(uint8_t id, uint8_t reg_addr, uint8_t *data, uint16_t len);
void user_delay_ms(uint32_t period);
void print_sensor_data(struct bme280_data *comp_data);
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);
int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev);

