#include "structs.h"
void enviarPCB(t_pcb* pcb, int socket){
	t_paquete* paquete= crear_paquete();
	//agregar_a_paquete(paquete, &(pcb->pid), sizeof(int));
	agregar_a_paquete(paquete, &(pcb->program_counter), sizeof(int));
	preparar_registros(paquete,pcb->register_cpu);
	enviar_paquete(paquete, socket);
	eliminar_paquete(paquete);
}
void preparar_registros(t_paquete *paquete, t_register_cpu register_cpu)
{
 	agregar_a_paquete(paquete, &(register_cpu.AX), sizeof(uint8_t));
	agregar_a_paquete(paquete, &(register_cpu.BX), sizeof(uint8_t));
	agregar_a_paquete(paquete, &(register_cpu.CX), sizeof(uint8_t));
	agregar_a_paquete(paquete, &(register_cpu.DX), sizeof(uint8_t));
	agregar_a_paquete(paquete, &(register_cpu.EAX), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.EBX), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.ECX), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.EDX), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.SI), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.PC), sizeof(uint32_t));
	agregar_a_paquete(paquete, &(register_cpu.DI), sizeof(uint32_t));
}

t_pcb* recibirPCB(int socket){
	t_list* valores_recibidos = recibir_paquete(socket);

    t_pcb* pcb_recibido = malloc(sizeof(t_pcb));
   
	pcb_recibido->quantum_restante = *((int*)list_get(valores_recibidos, 1));
	pcb_recibido->program_counter = *((int*)list_get(valores_recibidos, 2));
	recibir_registros(valores_recibidos,pcb_recibido);
	return pcb_recibido;
}

void recibir_registros(t_list* lista, t_pcb* pcb_recibido)
{
	pcb_recibido->register_cpu.AX = *((uint8_t*)list_get(lista, 3));
	pcb_recibido->register_cpu.BX = *((uint8_t*)list_get(lista, 4));
	pcb_recibido->register_cpu.CX = *((uint8_t*)list_get(lista, 5));
	pcb_recibido->register_cpu.DX = *((uint8_t*)list_get(lista, 6));
	pcb_recibido->register_cpu.EAX = *((uint32_t*)list_get(lista, 7));
	pcb_recibido->register_cpu.EBX = *((uint32_t*)list_get(lista, 8));
	pcb_recibido->register_cpu.ECX = *((uint32_t*)list_get(lista, 9));
	pcb_recibido->register_cpu.EDX = *((uint32_t*)list_get(lista, 10));
	pcb_recibido->register_cpu.SI = *((uint32_t*)list_get(lista, 11));
	pcb_recibido->register_cpu.DI = *((uint32_t*)list_get(lista, 12));
}

void mostrarPCB(t_pcb* proceso)
{
	printf("PID: %d\n", proceso->pid);
    			printf("Quantum Restante: %d\n", proceso->quantum_restante);
    			printf("Program Counter: %d\n", proceso->program_counter);
   				printf("Register CPU:\n");
				//CHEQUEAR LOS TIPOS DE DATOS
    			printf("  EAX: %d\n", proceso->register_cpu.EAX);
    			printf("  EBX: %d\n", proceso->register_cpu.EBX);
    			printf("  ECX: %d\n", proceso->register_cpu.ECX);
    			printf("  EDX: %d\n", proceso->register_cpu.EDX);
				printf("  AX: %d\n", proceso->register_cpu.AX);
				printf("  BX: %d\n", proceso->register_cpu.BX);
				printf("  CX: %d\n", proceso->register_cpu.DX);
				
				printf("  DX: %d\n", proceso->register_cpu.PC);
				printf("  BX: %d\n", proceso->register_cpu.SI);
				printf("  CX: %d\n", proceso->register_cpu.DI);
				
}