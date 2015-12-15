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

double random_value(double request_rate, double modulo) {
  double r;
  do
    r = uniform_deviate(rand());
  while (r == 0.0);

  r = (-log(r) * request_rate);
  if (modulo == 0.0) {
    return r;
  } else {
    return fmod(r, modulo);
  }
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

#ifdef DEBUG
  return;
#endif

  if (state->no != 0) {
    printf("%s -> ", format_time(state->time));

    /* switch to print out the correct event type */
    switch (state->event) {
    case PASSENGER_SUBSCRIPTION_EVENT:
      printf("new request placed from stop %d to stop %d for departure at %s scheduled for %s",
             state->passenger_subscription_event->departure,
             state->passenger_subscription_event->arrival,
             format_time(state->passenger_subscription_event->depart_at),
             format_time(state->passenger_subscription_event->scheduled_at));
      break;
    case PASSENGER_EMBARK_EVENT:
      break;
    case PASSENGER_DISEMBARK_EVENT:
      break;
    case BUS_ARRIVAL_EVENT:
      break;
    case BUS_DEPARTURE_EVENT:
      break;
    }

    printf("\n");
  }
}


/*
 * gets the next passenger subscription state
 */
struct State *next_passenger_state(struct State *old_state) {
  double r;
  double request_rate = old_state->config->request_rate;
  struct State *state = next_state(old_state);
  state->event = PASSENGER_SUBSCRIPTION_EVENT;
  state->passenger_subscription_event = malloc(sizeof(struct PassengerSubscriptionEvent));
  state->passenger_subscription_event->no = 0;


  /* stops must be uniformly random */
  state->passenger_subscription_event->departure = (int) random_value(request_rate, state->config->no_stops);
  state->passenger_subscription_event->arrival = (int) random_value(request_rate, state->config->no_stops);

  /* get wait time for passenger */
  {
    r = random_value(request_rate, 0);
    // int next_passenger = (int) (-log(r) * state->config->request_rate);
    int next_passenger = r;
    state->time = old_state->time + next_passenger;
  }
  r = random_value(request_rate, 0);
  {
    // int depart_time = (int) (-log(r) * state->config->request_rate);
    int depart_time = r;
    state->passenger_subscription_event->depart_at = state->time + depart_time;

    /* set this to the same time as the default */
    state->passenger_subscription_event->scheduled_at = state->passenger_subscription_event->depart_at;
  }

  return state;
}

/*
 * This returns the state of the next event.
 * it gets the possible states of the next possible states,
 * then iterates through them and finds the one with the shortest time to
 * execution.
 *
 * TODO: Calculate the estimated pickup time for passenger subscriptions
 */
struct State *create_new_state(struct State *old_state) {
  struct State *pickup = next_passenger_state(old_state);
  return pickup;
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
    output_state(state);
    state = tick(state);
  }

  stats->state = state;
  return stats;
}
