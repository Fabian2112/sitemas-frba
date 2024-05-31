#include <stdlib.h>
#include <stdio.h>
#include "io.h"

int main(int argc, char* argv[]) {
    io_config=iniciar_config(argv[1]);
    io_log=iniciar_log("io.log","io");
    obtenerValoresDeConfig(io_config, &tipoInterfaz, &tiempoTrabajo, &ipKernel, &puertoKernel, &ipMemoria, &puertoMemoria, 
                            &pathDialfs, &blockSize, &blockCount);
    printf("%s","Se está ejecuntado io");
        
    
    return 0;
}

void conectar_a_kernel(){
    socket_kernel=crear_conexion(ipKernel, puertoKernel);
    if(socket_kernel!=0){
        log_error(io_log, "No se ha podido conectar a Kernel");
    }else{
        log_info(io_log, "Se ha conectado con éxito");
    
    }
    //Necesitamos dos hilos, uno que recina de lista de kernle y vaya dejando en lista de espera y otro que vaya proceso la lista de espera.
    while(true){
    
        t_list* listaBloqueado=list_create();

        listaBloqueado=recibir_paquete(socket_kernel);
        t_proceso_bloqueado* procesoBloqueado= malloc(sizeof(t_proceso_bloqueado))
        procesoBloqueado->pid=*((int*)list_get(listaBloqueado,0));
        procesoBloqueado->motivo=*((int*)list_get(listaBloqueado,1));
        procesoBloqueado->unidadesTrabajo=*((int*)list_get(listaBloqueado,2));
        switch (procesoBloqueado->motivo)
        {
        case INTERFAZ_GENERICA:
            ejecutar_interfaz_Generica(procesoBloqueado);
            break;
        
        default:
            break;
        }
    }
};

void conectar_a_memoria(){
    socket_memoria=crear_conexion(ipMemoria, puertoMemoria);
    if(socket_memoria!=0){
        log_error(io_log, "No se ha podido conectar a memoria");
    }else{
        log_info(io_log, "Se ha conectado con éxito");
    }
}

void ejecutar_interfaz_Generica(t_proceso_bloqueado* proceso){
    
   sleep(proceso->unidadesTrabajo*tiempoTrabajo);
   send(socket_kernel,proceso->pid);
}