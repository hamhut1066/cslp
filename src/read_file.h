#ifndef READ_FILE_H_ /* include guard */
#include <libconfig.h>

#include "states.h"

#define READ_FILE_H_
#define BUFF_LEN 50

void read_config_file(struct Config *config, char* filename);
void parse_config(struct Config *state, config_t *config);

#endif
/* READ_FILE_H_ */
