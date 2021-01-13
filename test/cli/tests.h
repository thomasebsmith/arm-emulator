#ifndef TESTS_CLI_H
#define TESTS_CLI_H

#include "../shared/test_framework.h"

namespace Tests::CLI {
  TestFramework cli_parser_tests();

  TestFramework framework();
}

#endif
