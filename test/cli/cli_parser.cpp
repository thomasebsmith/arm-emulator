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
    test.that(
      "it parses a single argument correctly",
      []() {
        int argc = 2;
        char program_name[] = "/path/to/program";
        char argument[] = "some value - It shouldn't matter what's here\"\\";
        char *argv[] = {program_name, argument};
        try {
          CLIParser parser(argc, argv, {
            CLIParser::Argument{"the_argument", "argument", "description"}
          });
          auto arg = parser.get_argument("the_argument");
          confirm(!!arg, "Argument provided but not found");
          confirm(
            *arg == argument,
            std::string{"Incorrect argument value retrieved: Expected \""} +
              argument + "\" but found \"" + std::string{*arg} + '"'
          );
        }
        catch (const CLIParser::ParseException &err) {
          confirm(false, create_message(err));
        }
      }
    );
    test.that(
      "it fails if given extra flags",
      []() {
        int argc = 2;
        char program_name[] = "Program.exe";
        char flag[] = "--flag";
        char flag2[] = "-f";
        char *argv1[] = {program_name, flag};
        char *argv2[] = {program_name, flag2};
        bool error_thrown = false;
        try {
          CLIParser parser(argc, argv1, {});
        }
        catch (const CLIParser::ParseException &) {
          error_thrown = true;
        }
        confirm(error_thrown, "Expected error when given extra flags");

        error_thrown = false;
        try {
          CLIParser parser(argc, argv2, {
            CLIParser::Argument{"argument", "argument", "argument!"}
          });
        }
        catch (const CLIParser::ParseException &) {
          error_thrown = true;
        }
        confirm(error_thrown, "Expected error when given extra flags");
      }
    );
    test.that(
      "it fails if given extra arguments",
      []() {
        int argc = 2;
        char program_name[] = "my program name here";
        char argument[] = "argument-value-here";
        char *argv[] = {program_name, argument};
        bool error_thrown = false;
        try {
          CLIParser parser(argc, argv, {});
        }
        catch (const CLIParser::ParseException &) {
          error_thrown = true;
        }
        confirm(error_thrown, "Expected error when given extra argument");

        error_thrown = false;
        try {
          CLIParser parser(argc, argv, {
            CLIParser::Flag{'a', "argument-value-here", "description here"}
          });
        }
        catch (const CLIParser::ParseException &) {
          error_thrown = true;
        }
        confirm(error_thrown, "Expected error when given extra argument");
      }
    );
    test.that(
      "it can parse flags and arguments together",
      []() {
        int argc = 4;
        char program_name[] = "./the/program";
        char flag1[] = "--the-flag";
        char flag2[] = "-u";
        char argument[] = "\"the argument\"";
        char *argv[] = {program_name, flag1, argument, flag2};
        try {
          CLIParser parser(argc, argv, {
            CLIParser::Flag{'t', "the-flag", "description"},
            CLIParser::Flag{'u', "un-flag", "description"},
            CLIParser::Argument{"internal_name", "name", "description"},
            CLIParser::Flag{'a', "an-unused-flag", "description"}
          });
          confirm(parser.has_flag("the-flag"), "Failed to parse first flag");
          confirm(parser.has_flag("un-flag"), "Failed to parse second flag");
          confirm(
            !parser.has_flag("an-unused-flag"),
            "Unexpectedly had third flag"
          );
          auto arg = parser.get_argument("internal_name");
          confirm(!!arg, "Failed to parse the argument");
          confirm(*arg == argument, "Wrong value parsed for argument");
        }
        catch (const CLIParser::ParseException &err) {
          confirm(false, create_message(err));
        }
      }
    );
    return test;
  }
}
