#include "configo.h"



char* KEY_PUERTO_ESCUCHA = "PUERTO_ESCUCHA";
char* KEY_IP_MEMORIA = "IP_MEMORIA";
char* KEY_PUERTO_MEMORIA = "PUERTO_MEMORIA";
char* KEY_IP_CPU = "IP_CPU";
char* KEY_PUERTO_CPU_DISPATCH = "PUERTO_CPU_DISPATCH";
char* KEY_PUERTO_CPU_INTERRUPT = "PUERTO_CPU_INTERRUPT";
char* KEY_ALGORITMO_PLANIFICACION = "ALGORITMO_PLANIFICACION";
char* KEY_QUANTUM = "QUANTUM";
char* KEY_RECURSOS = "RECURSOS";
char* KEY_INSTANCIAS_RECURSOS = "INSTANCIAS_RECURSOS";
char* KEY_GRADO_MULTIPROGRAMACION = "GRADO_MULTIPROGRAMACION";


void obtenerValoresDeConfig(t_config* config, char** puertoEscucha, char** ipMemoria, char** puertoMemoria,
		char** ipCpu, char** puertoCpuDispatch, char** puertoCpuInterrupt, char** algoritmoPlanificacion,
        int* quantum, char*** recursos, char*** instanciasRecursos, int* gradoMultiprogramacion){
    
    *puertoEscucha = config_get_string_value(config, KEY_PUERTO_ESCUCHA);
	*ipMemoria = config_get_string_value(config, KEY_IP_MEMORIA);
	*puertoMemoria = config_get_string_value(config, KEY_PUERTO_MEMORIA);
	*ipCpu = config_get_string_value(config, KEY_IP_CPU);
	*puertoCpuDispatch = config_get_string_value(config, KEY_PUERTO_CPU_DISPATCH);
    *puertoCpuInterrupt = config_get_string_value(config, KEY_PUERTO_CPU_INTERRUPT);
	*algoritmoPlanificacion = config_get_string_value(config, KEY_ALGORITMO_PLANIFICACION);
	*quantum = atoi(config_get_string_value(config, KEY_QUANTUM));
    *recursos = config_get_array_value(config, KEY_RECURSOS);
	*instanciasRecursos = config_get_array_value(config, KEY_INSTANCIAS_RECURSOS);
	*gradoMultiprogramacion = atoi(config_get_string_value(config, KEY_GRADO_MULTIPROGRAMACION));
}