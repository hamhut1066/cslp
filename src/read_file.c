#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <libconfig.h>

#include "states.h"

#include "read_file.h"

/*
 * Key Value Struct
 * TODO: (Maybe pull out into generic functionality) (or maybe move into an in-memory db).
 */
struct Kv {
  char *key;
  char *value;
};

void parse_config(State *state, config_t *config) {
  double double_cfg;
  int int_cfg;

  if(config_lookup_int(config, "busCapacity", &int_cfg)) {
    state->bus_capacity = int_cfg;
  }

  if(config_lookup_int(config, "boardingTime", &int_cfg)) {
    state->boarding_time = int_cfg;
  }

  if(config_lookup_float(config, "requestRate", &double_cfg)) {
    state->request_rate = double_cfg;
  }

  if(config_lookup_float(config, "pickupInterval", &double_cfg)) {
    state->pickup_interval = double_cfg;
  }

  if(config_lookup_int(config, "maxDelay", &int_cfg)) {
    state->max_delay = int_cfg;
  }

  if(config_lookup_int(config, "noBuses", &int_cfg)) {
    state->no_buses = int_cfg;
  }

  if(config_lookup_int(config, "noStops", &int_cfg)) {
    state->no_stops = int_cfg;
  }

  if(config_lookup_int(config, "stopTime", &int_cfg)) {
    state->stop_time = int_cfg;
  }

}

/* void **read_config_file(char *buffer[], char* filename) { */

/*   FILE *f; */
/*   int char_code; */
/*   int i = 0; */
/*   int j = 0; */
/*   char line[100]; */
/*   f = fopen(filename, "r"); */

/*   if (f == NULL) { */
/*     err(1, "%s", filename); */
/*   } */

/*   while ((char_code = fgetc(f)) != EOF) { */
/*     char c = (char) char_code; */
/*     line[j] = c; */

/*     if(c == '\n') { */
/*       // clear newline; */
/*       line[j] = '\0'; */

/*       int len = strlen(line); */
/*       buffer[i] = calloc((len + 1), sizeof(char)); */
/*       buffer[i] = strcpy(buffer[i], line); */
/*       line[0] = '\0'; */
/*       j = 0; */
/*       i++; */
/*     } else { */
/*       line[j] = c; */
/*       j++; */
/*     } */

/*   } */
/*   if (!feof(f)) { */
/*     err(1, "fgetln: <%s>", filename); */
/*   } */
/*   fclose(f); */
/*   return NULL; */
/* } */

int read_config_file(config_t *config, char* filename) {
  config_init(config);
  config_set_options(config, CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS);
  config_set_options(config, CONFIG_OPTION_COLON_ASSIGNMENT_FOR_NON_GROUPS);

  return config_read_file(config, filename);
}
