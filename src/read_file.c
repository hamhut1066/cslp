#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"

char test_char(void) {
  return 'a';
}

int read_config_file(char* filename) {
  char buf[256];
  while (fgets (buf, sizeof(buf), stdin)) {
    printf("line: %s", buf);
  }
  if (ferror(stdin)) {
    fprintf(stderr, "Opps, error reading stdin\n");
    abort();
  }
  return 0;
}
