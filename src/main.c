#include <stdio.h>
#include <stdlib.h>

#include "read_file.h"
#include "whitedb/whitedb.h"

void usage() {
  printf("Usage: cslp [filename]\n");
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    usage();
    return 0;
  }
  char **buffer = malloc(BUFF_LEN * sizeof(char*));
  read_config_file(buffer, argv[1]);
  for (int i = 0; i < BUFF_LEN; i++) {
    /* printf("%s\n", buffer[i]); */
  }

  void *db, *rec, *rec2;
  wg_int enc, enc2;

  db = wg_attach_database("1000", 2000000);
  rec = wg_create_record(db, 10);
  rec2 = wg_create_record(db, 2);

  enc = wg_encode_int(db, 443);
  enc2 = wg_encode_str(db, "this is my string!", NULL);

  wg_set_field(db, rec, 7, enc);
  wg_set_field(db, rec2, 0, enc2);
  return 0;
}
