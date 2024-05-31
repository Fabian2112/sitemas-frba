#include "configo.h"


char* KEY_TIPO_INTERFAZ="TIPO_INTERFAZ";
char* KEY_TIEMPO_UNIDAD_TRABAJO="TIEMPO_UNIDAD_TRABAJO";
char* KEY_IP_KERNEL = "IP_KERNEL";
char* KEY_PUERTO_KERNEL = "PUERTO_KERNEL";
char* KEY_IP_MEMORIA = "IP_MEMORIA";
char* KEY_PUERTO_MEMORIA = "PUERTO_MEMORIA";
char* KEY_PATH_BASE_DIALFS="PATH_BASE_DIALFS";
char* KEY_BLOCK_SIZE="BLOCK_SIZE";
char* KEY_BLOCK_COUNT="BLOCK_COUNT";


void obtenerValoresDeConfig(t_config* config, char** tipoInterfaz, int* tiempoTrabajo, char** ipKernel, char** puertoKernel, char** ipMemoria,
		char** puertoMemoria, char** pathDialfs, int* blockSize, int* blockSize){
    
	*tipoInterfaz = config_get_string_value(config, KEY_TIPO_INTERFAZ);
	*tiempoTrabajo = atoi(config_get_string_value(config, KEY_TIEMPO_UNIDAD_TRABAJO));
	*ipKernel = config_get_string_value(config, KEY_IP_KERNEL);
	*puertoKernel = config_get_string_value(config, KEY_PUERTO_KERNEL);
	*ipMemoria = config_get_string_value(config, KEY_IP_MEMORIA);
	*puertoMemoria = config_get_string_value(config, KEY_PUERTO_MEMORIA);
    *pathDialfs = config_get_string_value(config, KEY_PATH_BASE_DIALFS);
	
	*blockSize = atoi(config_get_string_value(config, KEY_BLOCK_SIZE));
	*blockCount = atoi(config_get_string_value(config, KEY_BLOCK_COUNT)); 
	
}