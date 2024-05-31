
#ifndef CONFIGO_H_
#define CONFIGO_H_

#include <commons/config.h>
#include <stdlib.h>


void obtenerValoresDeConfig(t_config* config, char** puertoEscucha, char** ipMemoria, char** puertoMemoria,
		char** ipCpu, char** puertoCpuDispatch, char** puertoCpuInterrupt, char** algoritmoPlanificacion,
        int* quantum, char*** recursos, char*** instanciasRecursos, int* gradoMultiprogramacion);



#endif /* CONFIG_H_ */