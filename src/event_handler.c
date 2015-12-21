/*
 * This Contains the Main event loop.
 *
 * this was initially designed to hold the event-loop,
 * but I ended up writing it in controller.c instead.
 */

void run_simulation(int max_time) {
  int time;

  for (time = 0; time < max_time;) {
    int delay;
    // Determine Allowed Events
    // Determine a Delay depending on nearest event
    time += delay;

    // modify state accordingly
  }
}


