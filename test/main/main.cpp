#include <iostream>
#include "cli/cli_parser.h"
#include "../shared/test.h"
#include "../shared/test_framework.h"

#include "../cli/tests.h"

using CLI::CLIParser;

TestFramework get_test_framework() {
  TestFramework test{"main test suite"};
  test.include(Tests::CLI::framework());
  return test;
}

void print_failure(const Test::Failure &failure) {
  std::cerr << "Test FAILED: " << failure.reason << '\n';
  for (const auto &location : failure.test_stack_trace) {
    std::cerr << '\t' << location << '\n';
  }
}

int main(int argc, char *argv[]) {
  try {
    CLIParser cli{argc, argv, {
      CLIParser::Flag{'h', "help", "Show help"}
    }};

    if (cli.has_flag("help")) {
      cli.show_help(std::cout);
      return 0;
    }

    auto framework = get_test_framework();
    auto results = framework.run_all();

    bool test_failed = false;
    for (const auto &result : results) {
      if (result) {
        test_failed = true;
        print_failure(*result);
      }
    }

    if (test_failed) {
      return 1;
    }

    return 0;
  }
  catch (const CLIParser::ParseException &error) {
    std::cerr << error.what() << '\n';
    std::cerr << "Use --help for more information about using this program.\n";
    return 1;
  }

  return 0;
}
