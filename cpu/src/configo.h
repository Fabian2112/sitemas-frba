
#ifndef CONFIGO_H_
#define CONFIGO_H_

#include <commons/config.h>
#include <stdlib.h>


void obtenerValoresDeConfig(t_config* config, char** ipMemoria, char** puertoMemoria, 
		 char** puertoEscuchaDispatch, char** puertoEscuchaInterrupt,
		 int* cantEntradasTlb, char** algoritmoTlb);



#endif /* CONFIG_H_ */