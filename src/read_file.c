#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include <libconfig.h>

#include "states.h"

#include "read_file.h"

void parse_map(struct Config *state, config_setting_t *map_list) {
  int dim; /* This is working on the assumption of a square matrix */
  int i, j, array_elem;
  config_setting_t *array;

  dim = config_setting_length(map_list);
  state->dimension = dim;

  int **map = malloc(dim * sizeof(int*));
  /* populate and create the map as a 2-dimensional array */
  for(i = 0; i < dim; i++) {
    map[i] = malloc(dim * sizeof(int));
    array = config_setting_get_elem(map_list, i);
    if (array == NULL || map[i] == NULL) {
      printf("Array doesn't exist in map!: %d:%d", i, j);
    }

    for(j = 0; j < dim; j++) {
      array_elem = config_setting_get_int_elem(array, j);
      map[i][j] = array_elem;
    }
  }

  state->map = map;
}

void parse_config(struct Config *state, config_t *config) {
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

  config_setting_t *map_list = config_lookup(config, "map");
  parse_map(state, map_list);
}

void read_config_file(struct Config *config, char* filename) {
  config_t cfg;
  config_init(&cfg);
  config_set_options(&cfg, CONFIG_OPTION_COLON_ASSIGNMENT_FOR_GROUPS);
  config_set_options(&cfg, CONFIG_OPTION_COLON_ASSIGNMENT_FOR_NON_GROUPS);

  if(config_read_file(&cfg, filename)) {
    parse_config(config, &cfg);
  }
}
