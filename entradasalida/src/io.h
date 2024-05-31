#ifndef io_h_
#define io_h_

#include <commons/log.h>
#include <commons/config.h>
#include <shared/confandlog.h>
#include <shared/utils.h>
#include <shraed/structs.h>
#include "config.h"
t_log* io_log ;
t_config* io_config;
//variables de configs
char* tipoInterfaz;
int tiempoTrabajo;
char* ipKernel;
char* puertoKernel;
char* ipMemoria;
char* puertoMemoria;
char* pathDialfs;
int blockSize;
int blockCount;
//variables sockets
int socket_kernel,socket_memoria;

//funciones
void conectar_a_kernel();
void conectar_a_memoria();
#endif /* io_h_*/