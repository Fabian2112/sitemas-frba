#ifndef INSTRUCCIONES_H
#define INSTRUCCIONES_H

#include <shared/structs.h>


//variables
extern t_pcb* procesoRunning;



extern int socket_memoria;
void set(void *ptrRegistro, void *valor, size_t tamReg, size_t tamVal);
void sum(void *ptrRegistroDestino, void *ptrRegistroOrigen, size_t tamDestino, size_t tamOrigen);
void sub(void *ptrRegistroDestino, void *ptrRegistroOrigen, size_t tamDestino, size_t tamOrigen);
void jnz(void *registro, int nroInstruccion, int *program_counter, size_t tamReg);
void io_gen_sleep();

void execute(t_instruccion* instruccion_params);
t_instruccion* decode(char* lineaInstruccion);
char* fetch();
void* decodeRegister(char* registroBuscado);
size_t decodeSize(char* registroBuscado);

#endif