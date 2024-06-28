//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Version: 1.0				Fecha: 31/08/22
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#include <L4.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Definitions
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Prototypes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Variables
//-----------------------------------------------------------------------------
uint16_t humedad, presion, temperatura, lux, r21, r22;
uint8_t contador, s1, s2, user, isp, led, text[50];

//-----------------------------------------------------------------------------
// Code
//-----------------------------------------------------------------------------
int main(void) {
    Kit_Cortex_Init();
    printf("hola mundo");
    Save_Text("hola mundo");
    Get_Text_Saved(&text[0]);
    //Console_Uart("Mensaje: %s \n", text);
    //UART0_Write("Hola", 4);
    Console_Write(CONSOLE_ENABLE,"Mensaje: %s \r\n", text);
    while(1) {
        contador++;
        Display_Segments(contador);
        Delay(1000);
        humedad = Get_Humidity();
        Console_Write("Humedad: %d %%\r\n", humedad);
        presion = Get_Pressure();
        Console_Write("Presion: %d hPa\r\n", presion);
        temperatura = Get_Temperature();
        Console_Write("Temperatura: %d %cC\r\n", temperatura,176);
        lux = Get_Lux();
        Console_Write("Intesidad luminica: %d lux\r\n", lux);
        r21 = Get_R21();
        Console_Write("R21: %d \r\n", r21);
        r22 = Get_R22();
        Console_Write("R21: %d \r\n", r22);
        int statusCNY70 = Get_CNY70();
        Console_Write("CNY70: %d \r\n", statusCNY70);
        s1 = Get_Key_S1();
        s2 = Get_Key_S2();
        user = Get_Key_ISP();
        isp = Get_Key_USER();
        if(s1==0)
        	Led_On(BLUE);
        if(s2==0)
        	Led_On(RED);
        if(user==0)
        	Led_On(GREEN);
        if(isp==0)
        	Led_On(WBLUE);
    }
}
