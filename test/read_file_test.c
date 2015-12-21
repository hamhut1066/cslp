/* Tested file */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "cutest/CuTest.h"

#include "../src/read_file.h"
#include "../src/states.h"

#define SAMPLE_INPUT "./test/fs/input.in"
#define BAD_INPUT  "./test/fs/bad_config_file.in"

/*
 * constructs a test config file.
 */
struct Config *test_config(char *file) {
  struct Config *config = get_initial_config();

  read_config_file(config, file);

  return config;
}

/*
 * test the config file is properly configured.
 */
void parse_config_test(CuTest *tc) {
  struct Config *config = test_config(SAMPLE_INPUT);

  CuAssertIntEquals(tc, config->bus_capacity, 12);
  CuAssertIntEquals(tc, config->stop_time, 86400);

  CuAssertIntEquals(tc, config->map[0][0], 0);
  CuAssertIntEquals(tc, config->map[1][2], 5);
  CuAssertIntEquals(tc, config->map[3][2], -1);

  destroy_config(config);

}

/*
 * test parsing an incorrect config file
 */
void parse_bad_config_test(CuTest *tc) {
  struct Config *config = test_config(BAD_INPUT);

  CuAssertIntEquals(tc, config->bus_capacity, 12);
  CuAssertIntEquals(tc, config->stop_time, 86400);

  CuAssertIntEquals(tc, config->map[0][0], 0);
  CuAssertIntEquals(tc, config->map[1][2], 5);
  CuAssertIntEquals(tc, config->map[3][2], -1);


  destroy_config(config);
}

/*
 * test an integer linked-list.
 */
void test_ilist(CuTest *tc) {
  struct IList *list = malloc(sizeof(struct IList));
  list->length = 0;

  ilist_add(list, 3);

  CuAssertIntEquals(tc, 3, list->value);
  CuAssertIntEquals(tc, 1, list->length);

  ilist_add(list, 4);

  CuAssertIntEquals(tc, 3, list->value);
  CuAssertIntEquals(tc, 4, list->next->value);
  CuAssertIntEquals(tc, 2, list->length);

  CuAssertIntEquals(tc, 1, ilist_contains(list, 3));
  CuAssertIntEquals(tc, 0, ilist_contains(list, 5));


  free_ilist(list);
}


CuSuite* ReadFileGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, parse_config_test);
  SUITE_ADD_TEST(suite, parse_bad_config_test);
  SUITE_ADD_TEST(suite, test_ilist);
  return suite;
}
