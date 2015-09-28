#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include <stdio.h>

static void null_test_success(int state) {
}
int main(void) {
  expect_any(null_test_success, 2);
  null_test_success(2);
  return 0;
}
