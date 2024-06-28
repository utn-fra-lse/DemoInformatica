/*
 * json.parse
 * Sirve solo para keys cuyo value es un numero
 *
 * Se debe definir los campos key en la matriz keys
 * Se debe definir los cantidad de campos key en #define KEYS
 * En el vector value_keys se obtendran los resultados
 *
 */
#include <L3.json.parse.h>
#include "string.h"

const char key[KEYS][10] = {
		"leds",
		"buzzer",
		"dac",
		"segments"
};
int value_keys[KEYS];

//-----------------------------------------------------------------------------
char json_parse(char *json){
	char *p0,*p1,*p2, p3, a[6];
	char i, j = strlen(json)-1;
	if(*json != '{' || *(json+j)!='}') return JSON_ERROR;
	*(json+j) = ',';

	for(i=0;i<KEYS;i++){
		p0 = strstr(json, key[i]);
		p1 = strstr(p0, ":");
		p2 = strstr(p0, ",");
		p3 = 0;
		while(p1 != p2){
			p1++;
			a[p3] = *p1;
			p3++;
		}
		a[p3] = 0;
		value_keys[i] = atoi(a);
	}
	*(json+j) = '}';
	return JSON_SUCCESS;
}
//-----------------------------------------------------------------------------
