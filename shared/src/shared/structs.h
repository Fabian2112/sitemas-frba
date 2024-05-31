#ifndef structs
#define  structs

#include "confandlog.h"
#include<netdb.h>
#include <pthread.h>
#include "utils.h"
#include <readline/readline.h>
typedef struct t_register_cpu
{
    uint32_t PC;
    uint32_t DI;
    uint32_t EAX;
    uint32_t EBX;
    uint32_t ECX;
    uint32_t EDX;
    uint32_t SI;
    uint8_t AX;
    uint8_t BX;
    uint8_t CX;
    uint8_t DX;

} t_register_cpu;
typedef struct t_pcb 
{
int pid;
int quantum_restante;
int program_counter;
t_register_cpu register_cpu;
}t_pcb;

typedef struct t_proceso
{
    int pid;
    t_list* instrucciones;
}t_proceso;

typedef struct t_instruccion
{
    int codigo_instruccion;
    t_list* parametros;
    int cant_params;
}t_instruccion;

typedef struct{
	int pid;
	int motivo;
    int unidadesTrabajo;
}t_proceso_bloqueado;
//funciones

void enviarPCB(t_pcb* pcb, int socket);
void enviar_registros(t_paquete *paquete, t_register_cpu register);
t_pcb* recibirPCB(int socket);
void recibir_registros(t_list* lista, t_pcb* pcb_recibido);
void mostrarPCB(t_pcb* pcb);
void preparar_registros(t_paquete *paquete, t_register_cpu register_cpu);
#endif