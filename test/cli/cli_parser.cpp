#include <string>
#include "cli/cli_parser.h"
#include "../shared/test.h"
#include "../shared/test_framework.h"

using CLI::CLIParser;

std::string create_message(const CLIParser::ParseException &err) {
  std::string message = "Unexpected parse exception \"";
  message += err.what();
  message += '"';
  return message;
}

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
        catch (const CLIParser::ParseException &err) {
          confirm(false, create_message(err));
        }
      }
    );
    test.that(
      "it gives an error if no program name is provided",
      []() {
        bool exception_thrown = false;
        int argc = 0;
        char *argv[] = {nullptr};
        try {
          CLIParser parser(argc, argv, {});
        }
        catch (const CLIParser::ParseException &) {
          exception_thrown = true;
        }
        confirm(exception_thrown, "No exception was thrown");
      }
    );
    test.that(
      "it parses a single flag correctly",
      []() {
        int argc = 2;
        char program_name[] = "./program";
        char flag[] = "--a-Flag";
        char *argv[] = {program_name, flag};
        try {
          CLIParser parser(argc, argv, {
            CLIParser::Flag{'a', "a-Flag", "some flag"},
            CLIParser::Flag{'b', "a-flag", "some other flag"}
          });
          confirm(parser.has_flag("a-Flag"), "Flag provided but not found");
          confirm(!parser.has_flag("a-flag"), "Case insensitive flag parsing");
        }
        catch (const CLIParser::ParseException &err) {
          confirm(false, create_message(err));
        }
      }
    );
    return test;
  }
}
