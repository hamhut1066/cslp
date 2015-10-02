#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "read_file.h"

#ifndef __APPLE__
#include "compat.h"
#endif
char test_char(void) {
  return 'a';
}

char **read_config_file(char* filename) {

  char **buffer = malloc(50 * sizeof(char*));
  FILE *f;
  size_t len;
  char *line;
  int i = 0;

  f = fopen(filename, "r");
  if (f == NULL) {
    err(1, "%s", filename);
  }

  while ((line = fgetln(f, &len))) {
    buffer[i] = malloc(sizeof(char) * (len - 1));
    strncpy(buffer[i], line, len - 1);
    i++;
  }
  if (!feof(f)) {
    err(1, "fgetln: <%s>", filename);
  }
  return buffer;
}
