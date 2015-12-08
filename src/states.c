#include <stdlib.h>

#include "states.h"
#include "debug.h"
/*
 * Handles all state related things
 */

State *get_initial_state() {
  State *state = malloc(sizeof(State));
  if (state == NULL) {
    printf("Error Mallocing State\n");
    free(state);
    return NULL;
  }

  state->no = 0; /* TODO: ? maybe let user define the no? */

  return state;
}

struct Config *get_initial_config() {
  struct Config *config = malloc(sizeof(struct Config));
  if (config == NULL) {
    printf("Error mallocing Config\n");
    free(config);
    return NULL;
  }

  /* this default is needed to stop errors */
  config->no_stops = 0;

  return config;
}


void destroy_users(struct User *users) {
  if (users != NULL) {
    DEBUG_PRINT("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(users);
  }
}

void destroy_buses(struct Bus *buses) {
  if (buses != NULL) {
    DEBUG_PRINT("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(buses);
  }
}

void destroy_network(int **map, int dim) {
  int i;
  for(i = 0; i < dim; i++) {
    free(map[i]);
  }
  free(map);
}
void destroy_config(struct Config *conf) {
  if (conf != NULL) {
    destroy_network(conf->map, conf->no_stops);
  }
}

void destroy_state(State *state) {
  if (state != NULL) {
    destroy_users(state->users);
    destroy_buses(state->buses);
  }
}

void print_config(struct Config *config) {
  printf("{busCapacity: %d, boardingTime: %d, requestRate: %f, pickupInterval: %f, maxDelay: %d, noBuses: %d, noStops: %d, stopTime: %d}\n",
         config->bus_capacity,
         config->boarding_time,
         config->request_rate,
         config->pickup_interval,
         config->max_delay,
         config->no_buses,
         config->no_stops, // dimension of map
         config->stop_time
         );
  int i, j;
  if (config->map != NULL) {
    for(i = 0; i < config->no_stops; i++) {
      printf("[");
      for(j = 0; j < config->no_stops; j++) {
        if (config->map[i] != NULL) {
          printf("%dn ", config->map[i][j]);
        } else {
          printf("N ");
        }
      }
      printf("]\n");
    }
  }
}

/*
 * Sets the initial state of the program
 * The state is built from the passed in config file.
 */
void set_initial_state(State *state, struct Config *config) {
  /* assign the config so that it is accessible from State. */
  state->config = config;
}

void print_state(State *state) {
  print_config(state->config);
}
