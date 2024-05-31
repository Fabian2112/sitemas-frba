#include "configo.h"



char* KEY_PUERTO_ESCUCHA = "PUERTO_ESCUCHA";
char* KEY_TAM_MEMORIA="TAM_MEMORIA";
char* KEY_TAM_PAGINA="TAM_PAGINA";
char* KEY_PATH_INSTRUCCIONES= "PATH_INSTRUCCIONES";
char* KEY_RETARDO_RESPUESTA="RETARDO_RESPUESTA";


void obtenerValoresDeConfig(t_config* config, char** puertoEscucha, int* tamMemoria, int* tamPag, char** pathInstrucciones, int* retardoRta){
    
    *puertoEscucha = config_get_string_value(config, KEY_PUERTO_ESCUCHA);
	*tamMemoria = atoi(config_get_string_value(config,KEY_TAM_MEMORIA));
    *tamPag = atoi(config_get_string_value(config,KEY_TAM_PAGINA));
    *pathInstrucciones = config_get_string_value(config,KEY_PATH_INSTRUCCIONES);
    *retardoRta = atoi(config_get_string_value(config,KEY_RETARDO_RESPUESTA));
}