#include <L4.h>     /* funciones de LEDs, 7 segmentos, memoria FLASH, sensor ambiental (BME280) y sensor de luz (BH1750) */
#include <stdint.h> /* interrupciones estandar */
#include <string.h> /* cadena de caracteres */
#include <stdio.h>  /* entrada/salida estandar => scanf, printf y sprintf */
#include <stdlib.h> /* biblioteca estandar => funcion rand()*/

uint32_t entero_32bits_sin_signo;
uint16_t humedad, presion, temperatura, lux, r21, r22;
uint8_t contador=0, s1, s2;

int main(void) {
    Kit_Cortex_Init(); // Inicializa los perifericos del kit segun la placa a utilizar

    while(1){
        Led_On(RED);    //Enciende el led RED
        Led_Off(RED);   //Apaga el led RED
    } /* Bucle infinito */

    /* Tenemos que asegurarnos que el programa nunca salga del main */
}
