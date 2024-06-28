/*
 * json.parse
 * Sirve solo para keys cuyo value es un numero
 *
 * Se debe definir los campos key en la matriz keys
 * Se debe definir los cantidad de campos key en #define KEYS
 * En el vector value_keys se obtendran los resultados
 *
 */
#define KEYS			4
#define JSON_ERROR		-1
#define JSON_SUCCESS	0
// json parse
extern const char key[KEYS][10];
extern int value_keys[KEYS];

char json_parse(char *json);
