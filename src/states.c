#include <stdlib.h>
#include <libconfig.h>

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
    destroy_network(conf->map, conf->dimension);
    free(conf);
  }
}

void destroy_state(State *state) {
  if (state != NULL) {
    destroy_config(state->config);
    destroy_users(state->users);
    destroy_buses(state->buses);
  }
}

// TODO: make sure this does not become a god file.
void print_config(struct Config *config) {
  printf("{busCapacity: %d, boardingTime: %d, requestRate: %f, pickupInterval: %f, maxDelay: %d, noBuses: %d, noStops: %d, stopTime: %d}\n",
         config->bus_capacity,
         config->boarding_time,
         config->request_rate,
         config->pickup_interval,
         config->max_delay,
         config->no_buses,
         config->no_stops,
         config->stop_time
         );
  int i, j;
  for(i = 0; i < config->dimension; i++) {
    printf("[");
    for(j = 0; j < config->dimension; j++) {
      printf("%d, ", config->map[i][j]);
    }
    printf("]\n");
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
