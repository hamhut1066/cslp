#include "CuTest.h"
#include <string.h>

#include "../src/read_file.h"

char* StrToUpper(char* str) {
  return str;
}

void TestStrToUpper(CuTest *tc) {
  char* input = strdup("hello world");
  char* actual = StrToUpper(input);
  char* expected = "HELLO WORLD";
  CuAssertStrEquals(tc, expected, actual);
}

void TestFF(CuTest *tc) {
  test_char();
  //CuAssertStrEquals(tc, 'b', test_char());
}

CuSuite* StrUtilGetSuite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, TestStrToUpper);
  SUITE_ADD_TEST(suite, TestFF);
  return suite;
}
