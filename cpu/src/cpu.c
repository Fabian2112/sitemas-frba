#include <stdlib.h>
#include <stdio.h>

#include "cpu.h"
int main(int argc, char* argv[]) {
    cpu_config = iniciar_config(argv[1]);
    cpu_log = iniciar_log("cpu.log","CPU");
    obtenerValoresDeConfig(cpu_config, &ipMemoria, &puertoMemoria, &puertoEscuchaDispatch, &puertoEscuchaInterrupt, &cantEntradasTlb, &algoritmoTlb);
    server_fd_dispatch = iniciar_servidor("127.0.0.1", puertoEscuchaDispatch, cpu_log);
    server_fd_interrupt = iniciar_servidor("127.0.0.1", puertoEscuchaInterrupt, cpu_log);
    printf("%s", "Se está ejecutando CPU");
    return 0;
}

void conectar_a_memoria(){
    
    if((socket_memoria = crear_conexion(ipMemoria, puertoMemoria)) <= 0){
        log_error(cpu_log, "ERROR en la conexión");
    }
	else{
    	int identificador = CPU;
        
		send(socket_memoria, &identificador, sizeof(int), 0);
		

		log_info(cpu_log,"Conexion con memoria exitosa");
		
    }
}
void conectar_Kernel_Dispatch(){
    int socket_kernel_dispatch = esperar_cliente(server_fd_dispatch, &cpu_log);//global
    int peticion = recibir_operacion(socket_kernel_dispatch);
    if(peticion == KERNEL){
        log_info(cpu_log,"Enviar mensaje de confirmacion");
        bool resultadoOperacion = true;
        send(socket_kernel_dispatch, &resultadoOperacion, sizeof(bool), 0);
        log_info(cpu_log,"Mensaje de confirmacion enviado");
    }
    else{
        log_error(cpu_log, "ERROR en la peticion");
        
	}
    while (1)
	{
		
		int cod_op = recibir_operacion(socket_kernel_dispatch);
		switch (cod_op)
		{
		
		case PCB:
			t_pcb* proceso=recibirPCB(socket_kernel_dispatch);
			execute(decode(fetch()));
        }
    }
}
void conectar_Kernel_Interrupt(){
    int socket_kernel_interrupt = esperar_cliente(server_fd_interrupt, &cpu_log);//global
    int peticion = recibir_operacion(socket_kernel_interrupt);
    if(peticion == KERNEL){
        log_info(cpu_log,"Enviar mensaje de confirmacion");
        bool result = true;
        send(socket_kernel_interrupt, &result, sizeof(bool), 0);
        log_info(cpu_log,"Mensaje de confirmacion enviado");
    }
    else{
        log_error(cpu_log, "ERROR en la peticion");
        
	}
    while (1)
	{
		
		int cod_op = recibir_operacion(socket_kernel_interrupt);
		switch (cod_op)
		{
		
		case DESALOJAR_PROCESO:
			
			break;
        }
    }
}