#include <fstream>
#include <functional>
#include <iostream>
#include "cli/cli.h"
#include "meta/program_info.h"
#include "disassemble.h"

int main(int argc, char *argv[]) {
  try {
    CLI::CLI cli{argc, argv, {
      CLI::CLI::Flag{'h', "help", "Show help" },
      CLI::CLI::Flag{'v', "version", "Show version information"},
      CLI::CLI::Argument{"input_file", "file", "Get machine code from <file>"}
    }};

    if (cli.has_flag("help")) {
      cli.show_help(std::cout);
      return 0;
    }
    else if (cli.has_flag("version")) {
      std::cout << Meta::ProgramInfo::show_version_info;
      return 0;
    }
    else {
      if (auto file_name = cli.get_argument("input_file")) {
        std::ifstream input_file{*file_name};
        if (!input_file) {
          std::cerr << "Could not read file " << *file_name << ".\n";
          return 1;
        }
        return disassemble(input_file, std::cout, std::cerr);
      }
      else {
        return disassemble(std::cin, std::cout, std::cerr);
      }
    }
  }
  catch (CLI::CLI::ParseException &error) {
    std::cerr << error.what() << '\n';
    std::cerr << "Use --help for more information about using this program.\n";
    return 1;
  }
}
