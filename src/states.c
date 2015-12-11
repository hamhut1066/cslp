#include <stdlib.h>

#include "states.h"
#include "debug.h"
/*
 * Handles all state related things
 */

struct State *get_initial_state() {
  struct State *state = malloc(sizeof(struct State));
  if (state == NULL) {
    printf("Error Mallocing State\n");
    free(state);
    return NULL;
  }

  state->no = 0; /* TODO: ? maybe let user define the no? */
  state->time = 0; /* initial state is time 0 */

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

void destroy_state(struct State *state) {
  if (state != NULL) {
    destroy_users(state->users);
    destroy_buses(state->buses);
  }
}

void destroy_stats(struct Stats *stats) {
  if (stats != NULL) {
    destroy_state(stats->state);
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

struct Stats *new_stats() {
  struct Stats *stats = malloc(sizeof(struct Stats));

  return stats;
}

/*
 * Sets the initial state of the program
 * The state is built from the passed in config file.
 */
void set_initial_state(struct State *state, struct Config *config) {
  /* assign the config so that it is accessible from State. */
  state->config = config;
}

void print_state(struct State *state) {
  printf("No: %d - ", state->no);
  printf("Time: %d\n", state->time);
}

struct State *get_state(struct Config *config) {
  struct State *state;

  state = get_initial_state();
  set_initial_state(state, config);

  return state;
}

struct State *next_state(struct State *old_state) {

  struct State *state = get_initial_state();
  state->last = old_state;

  state->no = old_state->no + 1;
  state->config = old_state->config;
  state->time = old_state->time;
  return state;
}
