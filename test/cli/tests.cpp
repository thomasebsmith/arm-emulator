#include "../shared/test_framework.h"
#include "tests.h"

TestFramework Tests::CLI::framework() {
  TestFramework test{"CLI tests"};
  test.include(cli_parser_tests());
  return test;
}
