#ifndef READ_FILE_H_ /* include guard */
#include <libconfig.h>

#include "states.h"

#define READ_FILE_H_
#define BUFF_LEN 50

int read_config_file(config_t *config, char* filename);
void parse_config(State *state, config_t *config);

#endif
/* READ_FILE_H_ */
