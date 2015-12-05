#ifndef READ_FILE_H_ /* include guard */

#include "states.h"

#define READ_FILE_H_
#define BUFF_LEN 50

void read_config_file(struct Config *config, char* filename);
void parse_config(struct Config *state, char* config);

#endif
/* READ_FILE_H_ */
