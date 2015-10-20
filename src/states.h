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

