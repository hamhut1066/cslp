#include <stdlib.h>
#include <libconfig.h>

#include "states.h"
#include "debug.h"
/*
 * Handles all state related things
 */

State *state_initial_state() {
  State *state = malloc(sizeof(State));
  struct Config *config = malloc(sizeof(struct Config));
  if (state == NULL || config == NULL) {
    printf("Error Mallocing State\n");
    free(state);
    free(config);
    return NULL;
  }

  state->no = 0;
  state->config = config;

  return state;
}


void destroy_users(struct Users *users) {
  if (users != NULL) {
    DEBUG_PRINT("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(users);
  }
}

void destroy_buses(struct Buses *buses) {
  if (buses != NULL) {
    DEBUG_PRINT("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(buses);
  }
}
void destroy_config(struct Config *conf) {
  if (conf != NULL) {
    /* destroy_network(state->network); */
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
void print_state(State *state) {
  printf("No: %d\n", state->no);
  printf("{busCapacity: %d, boardingTime: %d, requestRate: %f, pickupInterval: %f, maxDelay: %d, noBuses: %d, noStops: %d, stopTime: %d}\n",
         state->config->bus_capacity,
         state->config->boarding_time,
         state->config->request_rate,
         state->config->pickup_interval,
         state->config->max_delay,
         state->config->no_buses,
         state->config->no_stops,
         state->config->stop_time
         );
  int i, j;
  for(i = 0; i < state->config->dimension; i++) {
    printf("[");
    for(j = 0; j < state->config->dimension; j++) {
      printf("%d, ", state->config->map[i][j]);
    }
    printf("]\n");
  }
}
