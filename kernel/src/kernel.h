#ifndef kernel_h_
#define kernel_h_
#include <commons/log.h>
#include <commons/config.h>
#include <shared/structs.h>
#include <semaphore.h>
#include <commons/collections/queue.h>
#include  "configo.h"
//-----------------------Variables de Config-----------------------
char* puertoEscucha;
char* ipMemoria;
char* puertoMemoria;
char* ipCpu;
char* puertoCpuDispatch; // a través de este puerto creamos una conexión para enviar el pcb
char* puertoCpuInterrupt;
char* algoritmoPlanificacion;
int quantum;
char** recursos;
char** instanciasRecursos;
int gradoMultiprogramacion;
t_log* kernel_log ;
t_config* kernel_config;

//-----------------------Listas-----------------------
t_list* listaInstrucciones;
t_list* listaProcesosReady;
t_list* listaProcesosTerminados;
t_list* listaNuevosProcesos;
t_list* procesosBloqueados;
//-----------------------Estructuras-----------------------
t_pcb* procesoRunning;

//variables globales
char* stringReady;
int PID_PROCESOS;
//-----------------------Variables sockets----------------------- 
int socket_cpu_dispatch;
int socket_memoria;
int socket_cpu_interrupt; 
int socket_io; //chequear si es global

//-----------------------Variables sockets----------------------- 
int server_fd;
//-----------------------Funciones-----------------------
void iniciarSemaforos();
t_pcb* generar_pcb();
int leerConsola();
void recibir_registros(t_list* lista, t_pcb* pcb_recibido);
t_pcb* recibirPCB(int socket);
//-----------------------Conexiones-----------------------
int conectar_a_memoria();
int conectar_cpu_dispatch();
int conectar_cpu_interrupt();

//-----------------------Funciones de planificadores-----------------------
void manejadorPlanificadorLargoPlazo();
void manejadorPlanificadorCortoPlazo(void* arg);
void iteratorReady(t_pcb* pcbActual);
void moveProcessFIFO(t_list* listaDesde, t_list* listaHasta);
void takeProcessNext(t_list* listaReady);
void desalojador_round_robin(void * arg);
void pausarPlanificadores();
void iniciarPlanificadores();
void agregando_a_newcola(t_pcb* pcb);

//-----------------------Semaforos binarios-----------------------

sem_t planiLargoPlazo;
sem_t planiCortoPlazo;
sem_t cantProcesosConcurrentes;
sem_t runningLibre;
sem_t cantProcesosEnReady;
sem_t modulosLevantados;
pthread_mutex_t cantProcesosEnNew;
#endif /* kernel_h_*/