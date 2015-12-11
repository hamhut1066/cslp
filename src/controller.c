#include "controller.h"
#include "states.h"

#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>

#define DAY_SECS 86400
#define HOUR_SECS 3600
#define MIN_SECS 60
#define TIME_SIZE 12

double uniform_deviate (int seed) {
  return seed * (1.0 / (RAND_MAX + 1.0));
}


/*
 * formats the time to be beautiful
 */
char *format_time(int time) {
  char *formatted_time = malloc(TIME_SIZE * sizeof(char));

  int days = time / DAY_SECS; /* seconds in a day */
  int hours = (time % DAY_SECS) / HOUR_SECS;
  int mins = ((time % DAY_SECS) % HOUR_SECS) / MIN_SECS;
  int secs = ((time % DAY_SECS) % HOUR_SECS) % MIN_SECS;

  sprintf(formatted_time, "%02d:%02d:%02d:%02d", days, hours, mins, secs);

  return formatted_time;
}

void output_state(struct State *state) {
  /* initial state does not have an event attached */
  if (state->no != 0) {
    printf("%s ->", format_time(state->time));
    printf("\n");
  }
}


/*
 * gets the next passenger subscription state
 */
struct State *next_passenger_state(struct State *old_state) {
  // return next_state(old_state);
  struct State *state = next_state(old_state);

  double r;

  /* extract into sub-method */
  do
    r = uniform_deviate(rand());
  while (r == 0.0);

  int next_passenger = (int) (-log(r) * state->config->request_rate);

  state->time = old_state->time + next_passenger;

  return state;
}

/*
 * This returns the state of the next event.
 * it gets the possible states of the next possible states,
 * then iterates through them and finds the one with the shortest time to
 * execution.
 */
struct State *create_new_state(struct State *old_state) {
  return next_passenger_state(old_state);
}
/*
 * This method performs one tick, and returns the new state.
 */
struct State *tick(struct State *state) {
  state = create_new_state(state);
  return state;
}

/*
 * This method sets up some basic things, then gets to work on the problem.
 */
struct Stats *run_experiment(struct State *state) {
  struct Stats *stats = new_stats();
  srand((int)time(NULL));
  rand(); /* calling once because first value is always the same */


  while (state->time < state->config->stop_time) {
    // TODO: add an event printer to the project.
    // output_state(state);
    state = tick(state);
  }

  stats->state = state;
  return stats;
}
