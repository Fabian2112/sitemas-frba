#include <stdlib.h>
#include <stdio.h>
//#include <utils.h>
#include "memoria.h"

int main(int argc, char* argv[]) {
    memoria_config = iniciar_config(argv[1]);
    memoria_log = iniciar_log("memoria.log","memoria");
    printf("%s", "Se está ejecutando memoria");
    obtenerValoresDeConfig(memoria_config, &puertoEscucha, &tamMemoria, &tamPag, &pathInstrucciones, &retardoRta);
    int socket_servidor = iniciar_servidor("127.0.0.1", puertoEscucha, memoria_log);
    

    pthread_t hilo_kernel, hilo_cpu;
    for (int i = 0; i < 2; i++){
        socket_cliente = esperar_cliente(socket_servidor,memoria_log);

        int cod_op = recibir_operacion(socket_cliente);

        switch (cod_op){
            case KERNEL:
                socket_kernel = socket_cliente;
                pthread_create(&hilo_kernel, NULL, (void *) conectarKernel, &socket_kernel);
                break;
            case CPU:
                socket_cpu = socket_cliente;
                pthread_create(&hilo_cpu, NULL, (void *) conectarCpu, &socket_cpu);
                break;
            default:
                printf("Codigo invalido");
                break;
        }
    }

    return 0;
}


//la memoria se encarga de crear un pcb y "llenarlo" (el PID se encarga de llenarlo el Kernel)
t_pcb* crear_PCB(){
    t_pcb* pcb= (t_pcb *) malloc(sizeof(t_pcb));
    iniciar_registros(&(pcb->register_cpu));
    pcb->program_counter = 0; //esto sirve para que el pcb pueda ejecutar la próxima instrucción 
    printf("Se ha creado un pcb\n");
    return pcb;
}



int conectarCpu(int* socket_cpu){
    bool resultadoPeticion = true;
    send(*socket_cpu, &resultadoPeticion, sizeof(bool), 0);
    while (true){
        int cod_op = recibir_operacion(*socket_cpu);
        switch (cod_op){
            case FETCH:
                int size=sizeof(int)*2;
                t_list * paqueteDesdeCpu = list_create();
                paqueteDesdeCpu = recibir_paquete(socket_cpu);
                int pid = (int)list_get(paqueteDesdeCpu, 0);
                int program_counter = (int)list_get(paqueteDesdeCpu, 1);
                printf("BUSCANDO INSTRUCCION....\n");
                usleep(1000);//retardo de la obtencion de la instruccion
                char* instruccion = buscarInstruccionProceso(pid, program_counter);
                t_paquete* paqueteParaCpu = crear_paquete();
                agregar_a_paquete(paqueteParaCpu, instruccion, strlen(instruccion)+1);
                enviar_paquete(paqueteParaCpu);
                break;
            default:
                printf("BUSCANDO INSTRUCCION....\n");
                break;
        }
    }
    
}
int conectarKernel(int* socket_kernel){
    bool resultadoPeticion = true;
    send(*socket_kernel, &resultadoPeticion, sizeof(bool), 0);
    while(true){
        int cod_op = recibir_operacion(*socket_kernel);
        switch (cod_op){
            case INICIAR_PROCESO:
                int size=sizeof(int);
                char* buffer = recibir_buffer((&size), *socket_kernel);
                int pid;
                printf("BUSCANDO INSTRUCCIONES...\n");
                memcpy(&pid, buffer, sizeof(int));
                //crear proceso, levantar archivo pseudocodigo, meter todas las instrucciones en ese proceso
                //agregar proceso a la lista de procesos
                t_proceso* procesoActual = malloc(sizeof(t_proceso));
                procesoActual->pid = pid;
                procesoActual->instrucciones = obtenerListaInstrucciones(pathInstrucciones);
                list_add(listaProcesos, procesoActual);
                break;
            case CREAR_PCB:
                t_pcb*  pcb=crear_PCB();
                printf("Se ha creado con éxito el pcb: %d\n",pcb->program_counter);
                enviarPCB(pcb,socket_kernel);
                printf("Se ha enviado PCB\n");
            default :
                printf("CODIGO INVALIDO \n");
                break;
        }
    }
}


t_list* obtenerListaInstrucciones(char* pathInstrucciones){
    FILE* file;
    file = fopen(pathInstrucciones, "rt");
    int numLineaActual = 0;
    char lineaActual[1000];
    t_list* listaInstrucciones = list_create();
    
    while(fgets(lineaActual, 1000, file) != NULL){
	    log_info(memoria_log, "for: %d", numLineaActual);
	    lineaActual[strcspn(lineaActual, "\n")] = 0;
	    char* nuevaLinea = malloc(strlen(lineaActual) + 1);
	    strcpy(nuevaLinea, lineaActual);
	    list_add(listaInstrucciones, nuevaLinea);
	    numLineaActual ++;
    }
    fclose(file);
    return listaInstrucciones;  
} 

char* buscarInstruccionProceso(int pid, int program_counter){
    pidBuscado = pid;
    t_proceso* proceso = list_find(listaProcesos, (void*) matchesPid);
    char* instruccionActual = list_get(proceso->instrucciones, program_counter);
    return instruccionActual;
}

bool matchesPid(t_proceso* proceso){
    return proceso->pid == pidBuscado;
}