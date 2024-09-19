# Demo para Informática I

Este proyecto puede descargarse e importarse en un workspace a gusto. Funciona independiente y cualquier actividad puede desarrollarse en [DemoInfo1.c](source/DemoInfo1.c).

## Info del kit

Puede hallarse el esquemático del kit en [BASE_KIT_V0](docs/BASE_KIT_V0.pdf) y el manual de usuario del LPC845 Breakout Board en el documento [UM11181](docs/UM11181.pdf).

## Documentación de funciones

Las funciones para usar se encuentran todas en [L4.c](source/L4.c)/[L4.h](source/L4.h). Entre las funciones que podremos usar se encuentran:

- `void Kit_Cortex_Init(void)` que inicializa los módulos del kit. Entre ellos:

    - Clock a 30MHz.
    - Pines digitales a botones y LEDs.
    - Systick a 1ms.
    - BME280 por SPI.
    - BH1750 por I2C.
    - ADC para R21 y R22.
    - Consola de debugueo si `CONSOLE_LOCAL` es 0. Consola por USART0 si `CONSOLE_LOCAL` es distinto de 0.

- `void Led_On(uint8_t led)` que se encarga de encender el LED indicado. Las opciones son:

    - `BLUE` para el LED azul del RGB.
    - `GREEN` para el LED verde del RGB.
    - `RED` para el LED rojo del RGB.
    - `WBLUE` para el LED azul del kit (D1).
    - Cualquier otra opción apaga todos los LEDs.

- `void Led_Off(uint8_t led)` que se encarga de apagar el LED indicado. Las opciones son:

    - `BLUE` para el LED azul del RGB.
    - `GREEN` para el LED verde del RGB.
    - `RED` para el LED rojo del RGB.
    - `WBLUE` para el LED azul del kit (D1).
    - Cualquier otra opción apaga todos los LEDs.

- `void Delay(uint32_t mseg)` genera una demora en milisegundos.

- `uint16_t Get_R21(void)` devuelve el valor analógico de R21 (0 a 4095).

- `uint16_t Get_R22(void)` devuelve el valor analógico de R22 (0 a 4095).

- `uint16_t Get_Temperature(void)` devuelve el valor de temperatura indicado por el BME280 en °C.

- `uint16_t Get_Humidity(void)` devuelve el valor de humedad relativa porcentual indicada por el BME280.

- `uint16_t Get_Pressure(void)` devuelve el valor de presión en hPa indicada por el BME280.

- `uint16_t Get_Lux(void)` devuelve la intensidad lumínica en LUX indicada por el BH1750.

- `void Display_Segments(uint8_t value)` escribe el valor indicado como parámetro en el display 7 segmentos siempre que sea menor a 100.

- `uint8_t Save_Text(uint8_t *text)` escribe en la flash el array o cadena de caracteres indicado como parámetro. Devuelve 0 si falló y distinto de 0 si fue un éxito la escritura.

- `void Get_Text_Saved(uint8_t *text)` guarda en el array o cadena pasada como parámetro el valor que haya en la flash.

- `uint8_t Get_Key_S1(void)` devuelve 0 si S1 fue presionada, sino devuelve distinto de 0.

- `uint8_t Get_Key_S2(void)` devuelve 0 si S2 fue presionada, sino devuelve distinto de 0.

- `uint8_t Get_Key_USER(void)` devuelve 0 si USER fue presionada, sino devuelve distinto de 0.

- `uint8_t Get_Key_ISP(void)` devuelve 0 si ISP fue presionada, sino devuelve distinto de 0.

- `uint8_t Get_Key_CNY70(void)` devuelve 0 si no hay objeto cerca del sensor. Devuelve 1 si tiene un objeto enfrentado. Tiene que tener el jumper de CN10 colocado en el CNY70.

- `void Console_Write(char console_uart, const char *format, ...)` escribe por consola el mensaje indicado siguiendo los estándares del printf.