#ifndef _STATES_H_
#define _STATES_H_
/*
 * This file encodes the possible states
 * each state will share some attributes,
 * such that they can be treated similarly in several contexts.
 */
struct Stop {
  int x;
  int y;
};


/*
 * passenger subscribes for a pickup.
 */
struct PassengerSubscriptionEvent {
  /*
   * the unique identifier for this passenger.
   * This no. is assigned when the passenger is recognised
   */
  int no;

  /* departure and arrival Stops */
  int departure;
  int arrival;

  /* time that the passenger wishes to depart */
  int depart_at;
  /* time that we schedule the passenger to depart */
  int scheduled_at;
};

struct BusDepartureEvent {};
struct BusArrivalEvent {};
struct PassengerDisembarkEvent {};
struct PassengerEmbarkEvent {};


/*
 * defined events that can occur in the system.
 */
#define PASSENGER_SUBSCRIPTION_EVENT 0
#define PASSENGER_EMBARK_EVENT       1
#define PASSENGER_DISEMBARK_EVENT    2
#define BUS_ARRIVAL_EVENT            3
#define BUS_DEPARTURE_EVENT          4

struct StopEdge {
  int time;
  struct Stop source;
  struct Stop dest;
};

struct User {
  /* implement as a singly linked list?... */
};
struct Bus {
  /* This will need to have a link to the current stop,*/
};
struct ServiceNetwork {
  struct Stop *stops; /* list of all available stops */
  struct StopEdge **routes;
}; // This needs to be thought about...

/*
 * Configuration Object
 * This object holds the configuration of the project.
 */
struct Config {

  int bus_capacity;
  int boarding_time;
  double request_rate;
  double pickup_interval;
  int max_delay;
  int no_buses;
  int no_stops;
  int **map;
  int stop_time;
  int dimension;
};

/*
 * This Defines a state of the program.
 * Note: The values are _essentially_ immutable, (althought technically not possible)
 *
 * IDEA: implement this as a singly linked-list? giving us the ability to walk through all the states?... (TODO)
 * i.e. State *next; &| State *prev;
 * This could be stored in whitedb, allowing for creating a StateReference, or something similar.
 */
struct State {
  /* defines the state no. this gives us the ablity to have a strictly ordered number of states */
  int no;
  struct State *last; /* last state */
  struct State *next; /* next state */
  struct State *first; /* first state */

  struct Config *config;

  /* to de dealt with */
  struct StopEdge *stops;
  struct User *users;
  struct Bus *buses;
  struct ServiceNetwork network;

  /* event that occurs at this state */
  int event;

  /* time that this state was reached */
  int time;

  /* event specific information states */
  struct PassengerSubscriptionEvent *passenger_subscription_event;
};

/*
 * This struct collects together all the relevant information for summarizing.
 */
struct Stats {
  /* holds the state of the experiment after completion */
  struct State *state;
};

/*
 * Helpers
 */

/*
 * extracts out the config and creates the initial state.
 */

/* create and destroy */
// void set_initial_state(State *state, struct Config *config);
struct State *next_state(struct State *old_state);
struct State *get_state(struct Config *config);
struct Config *get_initial_config();
struct Stats *new_stats();

void destroy_stats(struct Stats *stats);
void destroy_state(struct State *state);
void destroy_config(struct Config *config);

void print_config(struct Config *config);
void print_state(struct State *state);

#endif
