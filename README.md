# Informática I: Clase microcontroladores 


## Proyecto a importar en MCUXpresso

Este proyecto puede descargarse e importarse en un workspace. Funciona de forma independiente cuyo programa principal es [main.c](source/main.c).

## Pasos para importar el proyecto

- En cualquier workspace con al menos un proyecto, clickear en `Import project(s) from file system` e indicar la carpeta raiz de este repositorio.
- Compilar el proyecto mediante `Build Project`.
- Depurar el proyecto mediante `Debug As: MCUXpresso IDE LinkServer (inc. CMSIS-DAP) probes`.

## Kit de desarrollo LPC845

![Kit de desarrollo LPC845](docs/Kit_LPC845.png?raw=true)

## Información útil del kit

Puede hallarse el esquemático del kit en [BASE_KIT_V0](docs/BASE_KIT_V0.pdf) y el manual de usuario del LPC845 Breakout Board en el documento [UM11181](docs/UM11181.pdf).



## Ejercicios a realizar con kit de desarrollo LPC845
<ins>**Ejercicio 1.**</ins> **Encender** y **apagar** led **RED**

   _Nota: usar las funciones `void Led_On(uint8_t led)` y `void Led_Off(uint8_t led)`_

<br/>

<ins>**Ejercicio 2.**</ins> **Encender** y **apagar** led **RED** retardo con `for` ir probando con:
* `i < 1000`
* `i < 10000`
* `i < 100000`
* `...`

<br/>

<ins>**Ejercicio 3.**</ins> **Encender** led **WBLUE** durante **1 segundo** y **Apagar** led **WBLUE** durante **1 segundo**

   _Nota: usar la función `void Delay(uint32_t mseg)`_

<br/>

<ins>**Ejercicio 4.**</ins> **Contador de 0 a 10** en display 7 segmentos:
  - Incrementar valor cada **1 segundo**
  - Reiniciar el contador cuando su valor sea **mayor a 10**

  _Nota: usar la función `void Display_Segments(uint8_t value)`_

<br/>

<ins>**Ejercicio 5.**</ins> **Contador de 0 a 10** en display 7 segmentos:
  - Pulsador S1 incrementa valor / Pulsador S2 decrementa valor

  _Nota: usar las funciones `uint8_t Get_Key_S1(void)` y `uint8_t Get_Key_S2(void)`_

<br/>

<ins>**Ejercicio 6.**</ins> **Generar** un **Beep** de 500mseg cada vez que se presiona la tecla S1 y un **Sound** de 1 segundo a 1500Hz cada vez que se presiona la tecla S2

  _Nota: usar las funciones `void Beep(uint32_t mseg)` y `void Sound(uint32_t freq, uint32_t mseg)`_

<br/>

<ins>**Ejercicio 7.**</ins> **Dado electrónico** de 1 hasta 6:
  - Usar pulsador S1 para lanzar, al soltar S1 mostrar el número en el display 7 segmentos.

<br/>

<ins>**Ejercicio 8.**</ins> **Dado electrónico** de 1 hasta 6 usando la **funcion rand**:
  - Al apretar el pulsador S1 se deberán mostrar números tomados al azar cada `10ms` y al soltarlo debera quedar el último número mostrado.

<br/>

<ins>**Ejercicio 9.**</ins> **Leer `R22`**:
  - Si el valor está entre `0` y `900` encender led **RED** y apagar todos los demas
  - Si el valor está entre `901` y `1800` ecender led **GREEN** y apagar todos los demas
  - Si el valor está entre `1801` y `2700` se enciende led **BLUE** y apagar todos los demas
  - Si el valor está entre `2701` y `3600` se enciende led **WBLUE** y apagar todos los demas
  - Si **no se cumple ninguna de las condiciones** anteriores **todos** los **LEDs** deben estar **apagados**
 
  _Nota: usar la función `uint16_t Get_R22(void)`_

<br/>

<ins>**Ejercicio 10.**</ins> Modificar el **brillo** del led **WBLUE** en función al contador del **Ejercicio 5**
- Si el valor es `0` brillo al `0%`
- Si el valor es `1` brillo al `10%`
- Si el valor es `2` brillo al `20%`
- ...
- Si el valor es `9` brillo al `90%`
- Si el valor es `10` brillo al `100%`

  _Nota: usar la función `void Bright_Led(uint8_t bness)`

<br/>

<ins>**Ejercicio 11.**</ins> **Leer** la **temperatura**, **humedad** y **presión atmosférica** mediante el sensor **BME280**

_Nota: usar las funciones `uint16_t Get_Temperature(void)`, `uint16_t Get_Humidity(void)` y `uint16_t Get_Pressure(void)`_

<br/>

<ins>**Ejercicio 12.**</ins> **Leer** la cantidad de **lux** presentes en el sensor **BH1750**

_Nota: usar la función `uint16_t Get_Lux(void)`_

<br/>

## Documentación de funciones

Las funciones a utilizar están desarroladas en [L4.c](source/L4.c)/[L4.h](source/L4.h). Detalle de cada una de las funciones a utilizar:

```C
void Kit_Cortex_Init(void)
```
- Inicializa los módulos del kit. Entre ellos:

    - Clock a 30MHz.
    - Pines digitales a botones y LEDs.
    - Systick a 1ms.
    - Sensor ambiental BME280 (humedad, presion y temperatura) por SPI.
    - Sensor de luz BH1750 por I2C.
    - ADC para R21 y R22.
    - Consola de debugueo si `CONSOLE_LOCAL` es 0. Consola por USART0 si `CONSOLE_LOCAL` es distinto de 0.
<br/>

```C
void Led_On(uint8_t led)
```
- Se encarga de encender el LED indicado. Las opciones son:

    - `BLUE` para el LED azul del RGB.
    - `GREEN` para el LED verde del RGB.
    - `RED` para el LED rojo del RGB.
    - `WBLUE` para el LED azul del kit (D1).
    - `ALL_LEDS` prende todos los LEDs.
<br/>

```C
void Led_Off(uint8_t led)
```
- Se encarga de apagar el LED indicado. Las opciones son:

    - `BLUE` para el LED azul del RGB.
    - `GREEN` para el LED verde del RGB.
    - `RED` para el LED rojo del RGB.
    - `WBLUE` para el LED azul del kit (D1).
    - `ALL_LEDS` apaga todos los LEDs.
<br/>

```C
void Bright_Led(uint8_t bness)
```
- Se encarga de encender el led WBLUE con brillo entre 0 y 100.
<br/>

```C
void Delay(uint32_t mseg)
```
- Genera una demora en milisegundos.
<br/>

```C
uint16_t Get_R21(void)
```
- Devuelve el valor analógico de R21 (0 a 4095).
<br/>

```C
uint16_t Get_R22(void)
```
- Devuelve el valor analógico de R22 (0 a 4095).
<br/>

```C
void Sound(uint32_t freq, uint32_t mseg)
```
- Hace sonar el Buzzer a una frecuencia y un tiempo determinados.
<br/>

```C
void Beep(uint32_t mseg)
```
- Hace sonar el Buzzer a una frecuencia de 2500Hz durante un tiempo determinado.
<br/>

```C
uint16_t Get_Temperature(void)
```
- Devuelve el valor de temperatura indicado por el BME280 en °C.
<br/>

```C
uint16_t Get_Humidity(void)
```
- Devuelve el valor de humedad relativa porcentual indicada por el BME280.
<br/>

```C
uint16_t Get_Pressure(void)
```
- Devuelve el valor de presión en hPa indicada por el BME280.
<br/>

```C
uint16_t Get_Lux(void)
```
- Devuelve la intensidad lumínica en LUX indicada por el BH1750.
<br/>

```C
void Display_Segments(uint8_t value)
```
- Escribe el valor indicado como parámetro en el display 7 segmentos siempre que sea menor a 100.
<br/>

```C
uint8_t Save_Text(uint8_t *text)
```
- Escribe en la flash el array o cadena de caracteres indicado como parámetro. Devuelve 0 si falló y distinto de 0 si fue un éxito la escritura.
<br/>

```C
void Get_Text_Saved(uint8_t *text)
```
- Guarda en el array o cadena pasada como parámetro el valor que haya en la flash.
<br/>

```C
uint8_t Get_Key_S1(void)
```
- Devuelve 0 si S1 fue presionada, sino devuelve distinto de 0.
<br/>

```C
uint8_t Get_Key_S2(void)
```
- Devuelve 0 si el pulsador S2 fue presionado, sino devuelve distinto de 0.
<br/>

```C
uint8_t Get_Key_USER(void)
```
- Devuelve 0 si el pulsador USER fue presionado, sino devuelve distinto de 0.
<br/>

```C
uint8_t Get_Key_ISP(void)
```
- Devuelve 0 si el pulsador ISP fue presionado, sino devuelve distinto de 0.
<br/>

```C
uint8_t Get_Key_CNY70(void)
```
- Devuelve 0 si no hay un objeto cerca del sensor. Devuelve 1 si tiene un objeto enfrentado. Tiene que tener el jumper de CN10 colocado en el CNY70.
<br/>

```C
void Console_Write(char console_uart, const char *format, ...)
```
- Escribe por consola el mensaje indicado siguiendo los estándares del printf.
<br/>
