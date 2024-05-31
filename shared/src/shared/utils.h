#ifndef UTILSH
#define UTILSH

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<string.h>
#include<commons/log.h>
#include<commons/collections/list.h>
#include<commons/string.h>


typedef enum
{
    MENSAJE,
    PAQUETE,
    KERNEL,
    CPU,
    INICIAR_PLANIFICACION,
    DETENER_PLANIFICACION,
    LISTAR_PROCESOS,
    INICIAR_PROCESO,
    FINALIZAR_PROCESO,
    SET,
    SUM,
    SUB,
    JNZ,
    IO_GEN_SLEEP,
    INTERRUPCION,
    CREAR_PCB,
    ELIMINAR_PCB,
    PCB,
    FETCH,
    KERNEL_INTERRUPT,
    KERNEL_DISPATCH,
    INTERFAZ_GENERICA,
    DESALOJAR_PROCESO
}op_code;

typedef enum
{
    EXEC_RUNNING,
    EXEC_IO,
    EXEC_WAIT,
    EXEC_SIGNAL,
    EXEC_YIELD,
    EXEC_EXIT
}motivo_envio;

typedef struct
{
    int size;
    void* stream;
} t_buffer;

typedef struct
{
    op_code codigo_operacion;
    t_buffer* buffer;
} t_paquete;



int crear_conexion(char* ip, char* puerto);
void enviar_mensaje(char* mensaje, int socket_cliente);
t_paquete* crear_paquete(void);
void agregar_a_paquete(t_paquete* paquete, void* valor, int tamanio);
void enviar_paquete(t_paquete* paquete, int socket_cliente);
void liberar_conexion(int socket_cliente);
void eliminar_paquete(t_paquete* paquete);

void* recibir_buffer(int *, int);

int iniciar_servidor(char* ipEscucha, char* puertoEscucha, t_log* logger);
int esperar_cliente(int socket_servidor, t_log* logger);
t_list* recibir_paquete(int socket_cliente);
void recibir_mensaje(int socket_cliente, t_log* logger);
int recibir_operacion(int);
int transformar_codeop(char* op);

#endif /* UTILS_H */