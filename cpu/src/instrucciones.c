#include "instrucciones.h"

void set(void *ptrRegistro, void *valor, size_t tamReg, size_t tamVal){
    if(tamReg == tamVal){
        if(tamReg == sizeof(uint32_t)){
            *(uint32_t *) ptrRegistro = (uint32_t) valor;
        }
        else if(tamReg == sizeof(uint8_t)){
            *(uint8_t *) ptrRegistro = (uint8_t) valor;
        }
    }
}

void sum(void *ptrRegistroDestino, void *ptrRegistroOrigen, size_t tamDestino, size_t tamOrigen){
    if(tamDestino == tamOrigen){
        if(tamDestino == sizeof(uint32_t)){
            *(uint32_t *) ptrRegistroDestino = *(uint32_t*) ptrRegistroDestino + *(uint32_t*) ptrRegistroOrigen;
        }
        else if(tamDestino == sizeof(uint8_t)){
            *(uint8_t *) ptrRegistroDestino = *(uint8_t*) ptrRegistroDestino + *(uint8_t*) ptrRegistroOrigen ;
        }
    }
}

void sub(void *ptrRegistroDestino, void *ptrRegistroOrigen, size_t tamDestino, size_t tamOrigen){
    if(tamDestino == tamOrigen){
        if(tamDestino == sizeof(uint32_t)){
            *(uint32_t *) ptrRegistroDestino = *(uint32_t*) ptrRegistroDestino - *(uint32_t*) ptrRegistroOrigen;
        }
        else if(tamDestino == sizeof(uint8_t)){
            *(uint8_t *) ptrRegistroDestino = *(uint8_t*) ptrRegistroDestino - *(uint8_t*) ptrRegistroOrigen ;
        }
    }
}

void jnz(void *registro, int nroInstruccion, int *program_counter, size_t tamReg){
    if(tamReg == sizeof(uint32_t) && *(uint32_t *) registro == 0){
        *program_counter = nroInstruccion;
    }
    else if(tamReg == sizeof(uint8_t) && *(uint8_t *) registro == 0){
        *program_counter = nroInstruccion;
    }
}


char* fetch(){
    t_paquete* paquete = crear_paquete();
    agregar_a_paquete(paquete, procesoRunning->pid, sizeof(int));
    agregar_a_paquete(paquete, procesoRunning->program_counter, sizeof(int));
    enviar_paquete(paquete, socket_memoria);
    t_list* instruccionPaquete = list_create();
    instruccionPaquete = recibir_paquete(socket_memoria);
    char * instruccion;
    char* instruccioncopy=(char *) list_get(instruccionPaquete, 0);
    return memcpy(&instruccion,  instruccioncopy,strlen(instruccioncopy));
}

t_instruccion* decode(char* lineaInstruccion){
    //romper lineaInstruccion en "INSTRUCCION" y "LISTA[PARAMS]"
    //switch segun INSTRUCCION y usar la instruccion correspondiente utilizando los parametros correspondientes 
    //que ya sabemos que se usan
    t_instruccion* instruccion_params = malloc(sizeof(t_instruccion));
    char *instruccion;
    t_list *listaParam = list_create();
    char *token = strtok(lineaInstruccion, " ");
    
    if (token != NULL) {
        instruccion = strdup(token);
        token = strtok(NULL, " ");
        while (token != NULL) {
            list_add(listaParam, strdup(token));
            token = strtok(NULL, " ");
        }
    }
    instruccion_params->parametros = listaParam;
    if(strcmp(instruccion, "SET") == 0){
        instruccion_params->codigo_instruccion = SET;
        instruccion_params->cant_params = 2;
    }
    else if(strcmp(instruccion, "SUM") == 0){
        instruccion_params->codigo_instruccion = SUM;
        instruccion_params->cant_params = 2;
    }
    else if(strcmp(instruccion, "SUB") == 0){
        instruccion_params->codigo_instruccion = SUB;
        instruccion_params->cant_params = 2;
    }
    else if(strcmp(instruccion, "JNZ") == 0){
        instruccion_params->codigo_instruccion = JNZ;
        instruccion_params->cant_params = 2;
    }
    else if(strcmp(instruccion, "IO_GEN_SLEEP") == 0){
        instruccion_params->codigo_instruccion = IO_GEN_SLEEP;
        instruccion_params->cant_params = 2;
    }
    return instruccion_params;
}

void execute(t_instruccion* instruccion_params){
    char* primerParam = instruccion_params->cant_params > 0 ? list_get(instruccion_params->parametros, 0): "";
    char* segundoParam = instruccion_params->cant_params > 1 ? list_get(instruccion_params->parametros, 1): "";
    char* tercerParam = instruccion_params->cant_params > 2 ? list_get(instruccion_params->parametros, 2): "";
    switch(instruccion_params->codigo_instruccion){
        case SET:
            set(decodeRegister(primerParam), atoi(segundoParam), decodeSize(primerParam), decodeSize(primerParam));
        case SUM:
        case SUB:
            sum(decodeRegister(primerParam), decodeRegister(segundoParam), decodeSize(primerParam), decodeSize(segundoParam));
            break;
        case JNZ:
            jnz(decodeRegister(primerParam), atoi(segundoParam), &(procesoRunning->program_counter), decodeSize(primerParam));
            break;
    }
}

void* decodeRegister(char* registroBuscado) {
    if (strcmp(registroBuscado, "EAX") == 0) {
        return &(procesoRunning->register_cpu.EAX);
    } else if (strcmp(registroBuscado, "EBX") == 0) {
        return &(procesoRunning->register_cpu.EBX);
    } else if (strcmp(registroBuscado, "ECX") == 0) {
        return &(procesoRunning->register_cpu.ECX);
    } else if (strcmp(registroBuscado, "EDX") == 0) {
        return &(procesoRunning->register_cpu.EDX);
    } else if (strcmp(registroBuscado, "AX") == 0) {
        return &(procesoRunning->register_cpu.AX);
    } else if (strcmp(registroBuscado, "BX") == 0) {
        return &(procesoRunning->register_cpu.BX);
    } else if (strcmp(registroBuscado, "CX") == 0) {
        return &(procesoRunning->register_cpu.CX);
    } else if (strcmp(registroBuscado, "DX") == 0) {
        return &(procesoRunning->register_cpu.DX);
    } else if (strcmp(registroBuscado, "PC") == 0) {
        return &(procesoRunning->register_cpu.PC);
    } else if (strcmp(registroBuscado, "DI") == 0) {
        return &(procesoRunning->register_cpu.DI);
    } else if (strcmp(registroBuscado, "SI") == 0) {
        return &(procesoRunning->register_cpu.SI);
    }else {
        return NULL;
    }
}

size_t decodeSize(char* registroBuscado) {
    if (strcmp(registroBuscado, "EAX") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "EBX") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "ECX") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "EDX") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "AX") == 0) {
        return sizeof(uint8_t);
    } else if (strcmp(registroBuscado, "BX") == 0) {
        return sizeof(uint8_t);
    } else if (strcmp(registroBuscado, "CX") == 0) {
        return sizeof(uint8_t);
    } else if (strcmp(registroBuscado, "DX") == 0) {
        return sizeof(uint8_t);
    } else if (strcmp(registroBuscado, "PC") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "DI") == 0) {
        return sizeof(uint32_t);
    } else if (strcmp(registroBuscado, "SI") == 0) {
        return sizeof(uint32_t);
    }else {
        return NULL;
    }
}