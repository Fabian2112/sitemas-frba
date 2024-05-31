#include "confandlog.h"

t_log* iniciar_log(char * log , char *proceso)
{
    t_log* log_nuevo=log_create(log,proceso,1,LOG_LEVEL_INFO);
    if(log_nuevo==NULL) printf("%s", "No se ha podido crear log");
    return log_nuevo;
}
t_config* iniciar_config(char * arch)
{
    t_config* config_nuevo=config_create(arch);
    if(config_nuevo==NULL) printf("%s", "No se ha podido crear config");
    return config_nuevo;
}