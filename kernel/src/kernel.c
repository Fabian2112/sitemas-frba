#include <stdlib.h>
#include <stdio.h>
#include "kernel.h"

int main(int argc, char *argv[]) {
    kernel_config = iniciar_config(argv[1]);
    kernel_log = iniciar_log("kernel.log", "kernel");
    printf("%s\n", "Se está ejecutando Kernel");
	obtenerValoresDeConfig(kernel_config, &puertoEscucha, &ipMemoria, &puertoMemoria, &ipCpu, &puertoCpuDispatch, &puertoCpuInterrupt, 
							&algoritmoPlanificacion, &quantum, &recursos, &instanciasRecursos, &gradoMultiprogramacion);
	printf("Puerto escucha: %s\n", puertoEscucha);
	
	server_fd = iniciar_servidor("127.0.0.1", puertoEscucha, kernel_log);
	pthread_t t1,t2,t3,t4,t5,t6;
	printf("Termieno de iniciar servidor\n");
	pthread_create(&t4, NULL, (void*) leerConsola, NULL);	
	printf("Termieno de iniciar servido1r\n");
	pthread_create(&t1, NULL, (void*) conectar_a_memoria, NULL);
	/*pthread_create(&t2, NULL, (void*) conectar_cpu_dispatch, NULL);
	pthread_create(&t3, NULL, (void*) conectar_cpu_interrupt, NULL);
	
	pthread_create(&t5, NULL, (void*) manejadorPlanificadorLargoPlazo, NULL);
	pthread_create(&t6, NULL, (void*) manejadorPlanificadorCortoPlazo, (void*) algoritmoPlanificacion);

	 iniciarSemaforos();
    //Hacemos que los hilos sean independientes y liberen sus recursos cuando terminen  su ejecucion
	
	
    pthread_detach(t2);
    pthread_detach(t3);

    pthread_detach(t5);
    pthread_detach(t6);*/
	printf("Termieno de ejecutar\n");
	pthread_detach(t1);
	pthread_join(t4, NULL);//
	return 0;
}
int conectar_a_memoria(){
    printf("memoria\n");
	socket_memoria=-1;//para que se quede esperando la conexion
	while((socket_memoria)<=0)
    {	socket_memoria = crear_conexion(ipMemoria, puertoMemoria);
        log_error(kernel_log, "Intentando conectar a memoria");
		sleep(1);
    }
	//Acá voy verificando el protocolo de comunicación 
	int handshake_kernel=KERNEL;
	bool result;
	send(socket_memoria, &handshake_kernel, sizeof(int), 0);
	recv(socket_memoria, &result, sizeof(bool), MSG_WAITALL); //MSG_WAITALL esperará hasta que se reciba la cantidad completa de datos especificada por sizeof(bool) antes de devolver el control a tu programa
	if(result)
	{
			printf("COnexion existosa \n");
	}
	return 0;
}

int conectar_cpu_dispatch(){
	socket_cpu_dispatch=-1;//no creo y devuelvo el socket_dispatch, es mejor cargarlo en una variable globar para así no estar teniendo que conectar a cpu
	while((socket_cpu_dispatch = crear_conexion(ipCpu, puertoCpuDispatch))<=0){
        log_error(kernel_log, "No se ha podido conectar a cpu_Dispatch");

    }
	
	int handshake_kernel=KERNEL_DISPATCH;
	bool result;
	send(socket_cpu_dispatch, &handshake_kernel, sizeof(int), 0);
	recv(socket_cpu_dispatch, &result, sizeof(bool), MSG_WAITALL); //MSG_WAITALL esperará hasta que se reciba la cantidad completa de datos especificada por sizeof(bool) antes de devolver el control a tu programa
	if(result){
		printf("COnexion existosa \n");
	}
	return 0;
}

int conectar_cpu_interrupt(){
	socket_cpu_interrupt = -1;//no creo y devuelvo el socket_dispatch, es mejor cargarlo en una variable globar para así no estar teniendo que conectar a cpu
	if((socket_cpu_interrupt = crear_conexion(ipCpu, puertoCpuInterrupt))<=0){
        log_error(kernel_log, "No se ha podido conectar a cpu interrupt");

    }
	
	int handshake_kernel=KERNEL_INTERRUPT;
	bool result;
	send(socket_cpu_interrupt, &handshake_kernel, sizeof(int), 0);
	recv(socket_cpu_interrupt, &result, sizeof(bool), MSG_WAITALL); //MSG_WAITALL esperará hasta que se reciba la cantidad completa de datos especificada por sizeof(bool) antes de devolver el control a tu programa
	if(!result){
		 printf("SOCKET DE INTERRUPT PERTENECIENTE A KERNEL ESTÁ FALLANDO\n");
	}else  printf("SOCKET DE INTERRUPT todo ok\n");
	return 0;
}


void conectar_io() //recibe el motivo por el  cuál se interrumpio el proceso
{
	socket_io= esperar_cliente(server_fd,kernel_log);//chequear si es variable local
	while (true)
	{
		t_proceso_bloqueado* proximoProceso=list_get(procesosBloqueados,0);
		int motivo_bloqueo=proximoProceso->motivo;
		switch (motivo_bloqueo)//Acá vemos que tipo de opereación vamos a  hacerle al proceso bloqueado que viene en el motivo
		{
		case INTERFAZ_GENERICA:
			//send(proximoProceso,socket_io, sizeof(t_proceso_bloqueado), 0);
			t_paquete* paquete= crear_paquete();
		//agregar_a_paquete(paquete, &(pcb->pid), sizeof(int));
			agregar_a_paquete(paquete, &(proximoProceso->pid), sizeof(t_proceso_bloqueado));
			agregar_a_paquete(paquete, &(proximoProceso->motivo), sizeof(t_proceso_bloqueado));
			agregar_a_paquete(paquete, &(proximoProceso->unidadesTrabajo), sizeof(t_proceso_bloqueado));
			enviar_paquete(paquete, socket_io);
			eliminar_paquete(paquete);
			
			
			break;
		
		default:
			break;
		}
	}
	
}

//----------------------Consola----------------------
int leerConsola(){
	printf("Leer consola\n");
	char* entrada;
	entrada=readline("$ ");
	
	printf("COnsola leida\n");
	while(strcmp(entrada, "EXIT") != 0){
		printf("ENtro while\n");
		switch (transformar_codeop(entrada)){
			case INICIAR_PROCESO:
				int peticion=CREAR_PCB;
				send(socket_memoria, &peticion, sizeof(int), 0);
				t_pcb* proceso=recibirPCB(socket_memoria);//recibir pcb todavía no creada
				proceso->pid=PID_PROCESOS;
				PID_PROCESOS++;//chequear esto porque parece que para que yo tengo que enviar el pcb a través de un socket, se envían todos los datos incluyendo el PID 
				
				peticion=PCB;
				mostrarPCB(proceso);
				send(socket_cpu_dispatch,&peticion,sizeof(int), 0);
				printf("Se ha enviado el proceso a cpu \n");
				enviarPCB(proceso,socket_cpu_dispatch);
				//acordarse que al enviar pcb, tengo quitada el de asignar PID ya que lo puse en la carpeta shared. esto lo hice porque kernel le está asignando el PID y lo quite de enviarPCB así que enviarPCB no estaría enviando el PID. tendríamos q corregirlo
				agregando_a_newcola(proceso);
				break;
			case DETENER_PLANIFICACION:
				pausarPlanificadores();
				break;
			case INICIAR_PLANIFICACION:
				iniciarPlanificadores();
				break;
			default:
				printf("Ha ingresado una opción invalida.\n ");
				break;
		}
	}
	return 0 ; 
}
//----------------------PLANIFICADORES----------------------

void manejadorPlanificadorLargoPlazo(){
	//sem_wait() quería utilizar semáforos pero marea la implementación ya que este y el otro tendrían que ahcer dos veces wait al semaforo
	
	while(true){
		sem_wait(&planiLargoPlazo);//semaforo binario para ver si no está pausada la planificación
		pthread_mutex_lock(&cantProcesosEnNew);
		sem_wait(&cantProcesosConcurrentes);
		t_pcb* firstProcessInNewList = list_get(listaNuevosProcesos, 0);
		int pidFirstInNew = firstProcessInNewList->pid;
		log_info(kernel_log, "PID: %d - Estado Anterior: %s - Estado Actual: %s", pidFirstInNew, "NEW", "READY");
		moveProcessFIFO(listaNuevosProcesos, listaProcesosReady);
		stringReady = string_new();
		string_append(&stringReady, "[");
		list_iterate(listaProcesosReady, (void*) iteratorReady);//agrupa todos los procesos en ready y los separa por coma 
		string_append(&stringReady, "]");
		log_info(kernel_log, "Cola Ready %s: %s", algoritmoPlanificacion, stringReady);//imprime todos los procesos
		sem_post(&cantProcesosEnReady);
		sem_post(&planiLargoPlazo);
	}
	
}

void manejadorPlanificadorCortoPlazo(void* arg){
	char* algoritmoPlanif = (char*) arg;
	while(true){
		sem_wait(&planiCortoPlazo);//semaforo binario para ver si no está pausada la planificación
		sem_wait(&cantProcesosEnReady);
		sem_wait(&runningLibre);
		log_info(kernel_log, "PID: %d - Estado Anterior: %s - Estado Actual: %s", ((t_pcb*)list_get(listaProcesosReady, 0))->pid, "READY", "RUNNING");
		takeProcessNext(listaProcesosReady);
		enviarPCB(procesoRunning,socket_cpu_dispatch);
        //SI es rr y cumple quantum entonces mandamos al final de la cola ready
		printf("ProcesoRunning es enviado a la cpu\n");
        if(strcmp(algoritmoPlanif, "RR") == 0){
            //comparar tiempo_llegada_running y tiempo_actual vs quantum 
            //si supera, se lo manda al final de cola
            int *pid_ptr = malloc(sizeof(int));
			*pid_ptr=procesoRunning->pid;
			pthread_t round_robin;
			pthread_create(&round_robin, NULL, (void*) desalojador_round_robin,(void *) pid_ptr);
			
			pthread_detach(round_robin);
        }
		if(strcmp(algoritmoPlanif, "FIFO")==0){

		}
		sem_post(&planiCortoPlazo);
	}
}
void agregando_a_newcola(t_pcb* pcb){
    pthread_mutex_lock(&cantProcesosEnNew);
	list_add(listaNuevosProcesos, pcb);	 //agrega un elemento al final de la cola, función de la biblioteca common
    printf("Se ha agregado un nuevo elemento  a listaNuevosProcesos \n");
	pthread_mutex_unlock(&cantProcesosEnNew);
}

void pausarPlanificadores(){
	sem_wait(&planiLargoPlazo); //sem binario
	sem_wait(&planiCortoPlazo);
}
void iniciarPlanificadores(){
	sem_post(&planiLargoPlazo);
	sem_post(&planiCortoPlazo);
}

void takeProcessNext(t_list* listaReady){
	procesoRunning = (t_pcb*)list_remove(listaReady, 0);
}

void iteratorReady(t_pcb* pcbActual){
	int length = snprintf( NULL, 0, "%d", pcbActual->pid);
	char* str = malloc( length + 1 );
	snprintf( str, length + 1, "%d", pcbActual->pid ); //
	if(string_length(stringReady) > 1){
		string_append(&stringReady, ",");
	}
	string_append(&stringReady, str);
	free(str);
	//log_info(logger, "%d", pcbActual->pid);
}
//----------------------ALGORITMOS DE PLANIFICACIÓN----------------------
void moveProcessFIFO(t_list* listaDesde, t_list* listaHasta){
	t_pcb* pcbToMove = list_remove(listaDesde, 0);
	list_add(listaHasta, pcbToMove);
}
void desalojador_round_robin(void *arg){
	usleep(quantum);	
    sem_post(&runningLibre);
    
	//log_info("PID:%d - Desalojado por fin de Quantum", pid);//comento esto un rato q estoy poniendo d y pasando
	
} 
//----------------------INICIACIÓN DE SEMÁFOROS----------------------
void iniciarSemaforos(){
	sem_init(&planiLargoPlazo, 0, 0);
    sem_init(&planiCortoPlazo, 0, 0);
	pthread_mutex_init(&cantProcesosEnNew, NULL);
	sem_init(&cantProcesosConcurrentes,0,gradoMultiprogramacion);
}


//
