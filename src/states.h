#ifndef _STATES_H_
#define _STATES_H_
#include <libconfig.h>
/*
 * This file encodes the possible states
 * each state will share some attributes,
 * such that they can be treated similarly in several contexts.
 */

struct PassengerSubscriptionEvent {};
struct BusDepartureEvent {};
struct BusArrivalEvent {};
struct PassengerDisembarkEvent {};
struct PassengerEmbarkEvent {};


/*
 * Generic Event Struct which will contain an identifier,
 * allowing for passing around one struct and only pulling out information where necessary
 */
typedef struct {
  /* Identifies the 'sub-struct that contains the event information' */
  char identifier;

  /* Defined Events */
  struct PassengerSubscriptionEvent a;
  struct PassengerEmbarkEvent b;
  struct PassengerDisembarkEvent c;
  struct BusArrivalEvent d;
  struct BusDepartureEvent e;
} Event;

struct Stops {}; // Stops may be able to be marked on the ServiceNetwork
struct Users {}; // State will be had
struct Buses {}; // These have state, and will need to be stored
struct ServiceNetwork {}; // This needs to be thought about...

/*
 * This Defines a state of the program.
 * Note: The values are _essentially_ immutable, (althought technically not possible)
 *
 * IDEA: implement this as a singly linked-list? giving us the ability to walk through all the states?... (TODO)
 * i.e. State *next; &| State *prev;
 * This could be stored in whitedb, allowing for creating a StateReference, or something similar.
 */
typedef struct {
  /* defines the state no. this gives us the ablity to have a strictly ordered number of states */
  int no;

  int bus_capacity;
  int boarding_time;
  double request_rate;
  double pickup_interval;
  int max_delay;
  int no_buses;
  int no_stops;
  /* implement map */
  int stop_time;

  struct Users *users;
  struct Buses *buses;
  struct ServiceNetwork network;
} State;

// TODO: implement state specific methods (i.e... print_state)


/*
 * Helpers
 */

/*
 * extracts out the config and creates the initial state.
 */
State *state_initial_state();
void destroy_state(State *state);
void print_state(State *state);
#endif
