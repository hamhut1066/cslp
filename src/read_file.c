#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "read_file.h"

void **read_config_file(char *buffer[], char* filename) {

  FILE *f;
  int char_code;
  int i = 0;
  int j = 0;
  char line[100];
  f = fopen(filename, "r");

  if (f == NULL) {
    err(1, "%s", filename);
  }

  while ((char_code = fgetc(f)) != EOF) {
    char c = (char) char_code;
    line[j] = c;

    if(c == '\n') {
      // clear newline;
      line[j] = '\0';

      int len = strlen(line);
      buffer[i] = calloc((len + 1), sizeof(char));
      buffer[i] = strcpy(buffer[i], line);
      line[0] = '\0';
      j = 0;
      i++;
    } else {
      line[j] = c;
      j++;
    }

  }
  if (!feof(f)) {
    err(1, "fgetln: <%s>", filename);
  }
  return NULL;
}
