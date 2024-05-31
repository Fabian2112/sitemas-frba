#include "configo.h"



char* KEY_IP_MEMORIA = "IP_MEMORIA";
char* KEY_PUERTO_MEMORIA = "PUERTO_MEMORIA";
char* KEY_PUERTO_ESCUCHA_DISPATCH = "PUERTO_ESCUCHA_DISPATCH";
char* KEY_PUERTO_ESCUCHA_INTERRUPT = "PUERTO_ESCUCHA_INTERRUPT";
char* KEY_CANTIDAD_ENTRADAS_TLB = "CANTIDAD_ENTRADAS_TLB";
char* KEY_ALGORITMO_TLB = "ALGORITMO_TLB";




void obtenerValoresDeConfig(t_config* config, char** ipMemoria, char** puertoMemoria, 
		 char** puertoEscuchaDispatch, char** puertoEscuchaInterrupt,
		 int* cantEntradasTlb, char** algoritmoTlb){

	*ipMemoria = config_get_string_value(config, KEY_IP_MEMORIA);
	*puertoMemoria = config_get_string_value(config, KEY_PUERTO_MEMORIA);
	*puertoEscuchaDispatch = config_get_string_value(config, KEY_PUERTO_ESCUCHA_DISPATCH);
    *puertoEscuchaInterrupt = config_get_string_value(config, KEY_PUERTO_ESCUCHA_INTERRUPT);
	*algoritmoTlb = config_get_string_value(config, KEY_ALGORITMO_TLB);
	*cantEntradasTlb = atoi(config_get_string_value(config, KEY_CANTIDAD_ENTRADAS_TLB));
}