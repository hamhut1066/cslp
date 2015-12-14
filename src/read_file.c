#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "states.h"

#include "read_file.h"

void read_config_file(struct Config *cfg, char* filename) {
  FILE *pFile;
  char mystring [100];
  char key [100];
  int value;
  int processing_map = 0;
  int map_iter = 0;;

  pFile = fopen(filename, "r");
  if (pFile == NULL) perror("Error opening file");
  else {
    while (fgets(mystring, 100, pFile) != NULL) {
      sscanf(mystring, "%s %d", key, &value);
      if (strncmp(key, "#", 1) == 0) {}
      else if (processing_map) {
        /* Processes the map, needs to implement one line at a time */
        int *map = malloc(cfg->no_stops * sizeof(int));
        int i = 0;
        char *token = strtok(mystring, " ");
        while (token) {
          int val = strtol(token, NULL, 10);
          token = strtok(NULL, " ");
          map[i++] = val;
        }
        cfg->map[map_iter++] = map;
        if (++processing_map > cfg->no_stops) {
          processing_map = 0;
        }
      } else if (strncmp(key, "map", 3) == 0) {
        /* Throw decent error if map found before no_stops */
        if (cfg->no_stops == 0) {
          printf("The No. of stops must be provided before the map.\n");
          printf("Exiting...\n");
          exit(1);
        }
        processing_map = 1;
      } else {
        if (strncmp(key, "busCapacity", 100) == 0) {
          cfg->bus_capacity = value;
        } else if (strncmp(key, "boardingTime", 100) == 0) {
          cfg->boarding_time = value;
        } else if (strncmp(key, "requestRate", 100) == 0) {
          cfg->request_rate = value;
        } else if (strncmp(key, "pickupInterval", 100) == 0) {
          cfg->pickup_interval = value;
        } else if (strncmp(key, "maxDelay", 100) == 0) {
          cfg->pickup_interval = value;
        } else if (strncmp(key, "noBuses", 100) == 0) {
          cfg->no_buses = value;
        } else if (strncmp(key, "noStops", 100) == 0) {
          cfg->no_stops = value;
          cfg->map = malloc(value * sizeof(int*));
        } else if (strncmp(key, "stopTime", 100) == 0) {
          cfg->stop_time = value;
        } else {
          printf("You forgot to implement something: %s\n", key);
        }
      }
    }
    fclose (pFile);
  }

  /* config customization */

  /* hours to seconds gives us uniques times for everything */
  cfg->stop_time = cfg->stop_time * 60 * 60;
}
