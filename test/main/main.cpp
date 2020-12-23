#include <iostream>
#include "cli/cli_parser.h"

using CLI::CLIParser;

int main(int argc, char *argv[]) {
  try {
    CLIParser cli{argc, argv, {
      CLIParser::Flag{'h', "help", "Show help"}
    }};

    if (cli.has_flag("help")) {
      cli.show_help(std::cout);
      return 0;
    }

    std::cout << "TODO: Run tests.\n";
    return 0;
  }
  catch (const CLIParser::ParseException &error) {
    std::cerr << error.what() << '\n';
    std::cerr << "Use --help for more information about using this program.\n";
    return 1;
  }

  return 0;
}
