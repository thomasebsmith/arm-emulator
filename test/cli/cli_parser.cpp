#include <string>
#include "cli/cli_parser.h"
#include "../shared/test.h"
#include "../shared/test_framework.h"

using CLI::CLIParser;

namespace Tests::CLI {
  TestFramework cli_parser_tests() {
    TestFramework test{"CLIParser tests"};
    test.that(
      "it can parse empty arguments",
      []() {
        int argc = 1;
        char program_name[] = "some program name";
        char *argv[] = {program_name};
        try {
          CLIParser parser{argc, argv, {}};
        }
        catch (CLIParser::ParseException &err) {
          std::string assertion_message = "Unexpected parse exception \"";
          assertion_message += err.what();
          assertion_message += '"';
          confirm(false, assertion_message);
        }
      }
    );
    return test;
  }
}
