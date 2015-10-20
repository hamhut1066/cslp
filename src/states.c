#include <stdlib.h>
#include <libconfig.h>

#include "states.h"
/*
 * Handles all state related things
 */

State *state_initial_state() {
  State *state = malloc(sizeof(State));
  if (state == NULL) {
    return NULL;
  }

  state->no = 0;

  return state;
}


void destroy_users(struct Users *users) {
  if (users != NULL) {
    printf("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(users);
  }
}

void destroy_buses(struct Buses *buses) {
  if (buses != NULL) {
    printf("This needs to go through the array and delete everything");
    exit(EXIT_FAILURE);
    free(buses);
  }
}
void destroy_state(State *state) {
  if (state != NULL) {
    destroy_users(state->users);
    destroy_buses(state->buses);
    /* destroy_network(state->network); */
    free(state);
  }
}
// TODO: make sure this does not become a god file.
void print_state(State *state) {
  printf("No: %d\n", state->no);
  printf("{busCapacity: %d, boardingTime: %d, requestRate: %f, pickupInterval: %f, maxDelay: %d, noBuses: %d, noStops: %d, stopTime: %d}",
         state->bus_capacity,
         state->boarding_time,
         state->request_rate,
         state->pickup_interval,
         state->max_delay,
         state->no_buses,
         state->no_stops,
         state->stop_time
         );
}
