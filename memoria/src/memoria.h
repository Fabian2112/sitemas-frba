#ifndef memoria_h_
#define memoria_h_
#include <commons/log.h>
#include <commons/config.h>
#include <shared/confandlog.h>
#include  "configo.h"
#include <shared/utils.h>
#include <shared/structs.h>

t_log* memoria_log ;
t_config* memoria_config;
//configs de memoria 
int socket_cliente,socket_cpu,socket_kernel;
char* puertoEscucha;
int tamMemoria;
int tamPag;
char* pathInstrucciones;
int retardoRta;
int pidBuscado;

//sockets

int socket_kernel;
int socket_cpu;
//variables
int pid;
int program_counter;
//listas
t_list* listaProcesos;
//funciones


t_pcb* crear_PCB();
int conectarCpu(int* socket_cpu);
int conectarKernel(int* socket_kernel);
t_list* obtenerListaInstrucciones(char* pathInstrucciones);
char* buscarInstruccionProceso(int pid, int program_counter);
bool matchesPid(t_proceso* proceso);




#endif /* memoria_h_*/