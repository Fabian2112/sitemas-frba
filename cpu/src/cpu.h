#ifndef cpu_h_
#define cpu_h_
#include <shared/confandlog.h>
#include <commons/log.h>
#include <commons/config.h>
#include <shared/utils.h>
#include "configo.h"
#include "instrucciones.h"
t_log* cpu_log ;
t_config* cpu_config;
//valores configs
char* ipMemoria;
char* puertoMemoria;
char* puertoEscuchaDispatch;
char* puertoEscuchaInterrupt;
int cantEntradasTlb;
char* algoritmoTlb;
//variables conexiones
int server_fd_dispatch;
int server_fd_interrupt;
 t_pcb* procesoRunning;



int socket_memoria;
 //listas

//Funciones
int recibir_operacion(int socket);

void conectar_a_memoria();
void conectar_Kernel_Dispatch();
void conectar_Kernel_Interrupt();
#endif /* cpu_h_*/