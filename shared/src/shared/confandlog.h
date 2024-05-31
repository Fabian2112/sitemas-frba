#ifndef CONF_AND_LOG
#define  CONF_AND_LOG

#include <stdlib.h>
#include <commons/log.h>
#include<commons/string.h>
#include <commons/config.h>
#include<readline/readline.h>
t_config* iniciar_config(char* arch);
t_log* iniciar_log(char *log, char* proceso);

#endif
