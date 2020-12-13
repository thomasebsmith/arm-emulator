#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>
#include "cli/cli.h"

CLI::CLI::ParseException::ParseException(const std::string &error_message):
  std::runtime_error{error_message}
{}

CLI::CLI::CLI(int argc, char *argv[], const std::vector<Option> &options) {
  (void) argc;
  (void) argv;
  (void) options;
  throw ParseException("This is not yet implemented.");
}

bool CLI::CLI::has_flag(const std::string_view full_name) {
  (void) full_name;
  throw ParseException("This is not yet implemented.");
}

std::optional<std::string_view> CLI::CLI::get_argument(
  const std::string_view internal_name
) {
  (void) internal_name;
  throw ParseException("This is not yet implemented.");
}

std::ostream &CLI::CLI::show_help(std::ostream &out) {
  // TODO
  out << "Help here.\n";
  return out;
}
