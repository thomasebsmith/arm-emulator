#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>
#include "cli/cli.h"


template <typename T>
constexpr bool false_v = false;

CLI::CLI::ParseException::ParseException(const std::string &error_message):
  std::runtime_error{error_message}
{}

CLI::CLI::CLI(int argc, char *argv[], const std::vector<Option> &options) {
  if (argc == 0) {
    throw ParseException("No program name given");
  }

  for (const auto &option_variant : options) {
    std::visit([=](auto &&option) {
      using OptionT = std::decay_t<decltype(option)>;
      if constexpr (std::is_same_v<OptionT, Argument>) {
        possible_arguments.push_back(option);
      }
      else if constexpr (std::is_same_v<OptionT, Flag>) {
        if (!possible_flags.insert({option.full_name, option}).second) {
          throw ParseException("Repeated option " + option.full_name);
        }
        if (!flag_shortcuts.insert({
          option.shortcut,
          option.full_name
        }).second) {
          throw ParseException(
            std::string("Repeated option shortcut ") + option.shortcut
          );
        }
      }
      else {
        static_assert(false_v<OptionT>, "Unexpected CLI option variant");
      }
    }, option_variant);
  }

  bool raw_arguments = false;
  for (int i = 1; i < argc; ++i) {
    const std::string &argument = argv[i];
    if (raw_arguments || argument == "-" || argument.rfind("-", 0) != 0) {
      assert(arguments.size() <= possible_arguments.size());
      if (arguments.size() == possible_arguments.size()) {
        throw ParseException("Unnecessary argument " + argument);
      }
      arguments.push_back(argument);
    }
    else if (argument == "--") {
      raw_arguments = true;
    }
    else {
      assert(argument.length() > 1);
      assert(argument[0] == '-');
      if (argument[1] == '-') {
        // Option begins with --
        assert(argument.length() > 2);
        auto flag_name = argument.substr(2);
        if (possible_flags.find(flag_name) == possible_flags.end()) {
          throw ParseException("Unknown flag " + argument);
        }
        if (!flags.emplace(std::move(flag_name)).second) {
          throw ParseException("Repeated flag " + argument);
        }
      }
      else {
        // Option begins with -
        for (size_t i = 1; i < argument.length(); ++i) {
          char shortcut = argument[i];
          auto it = flag_shortcuts.find(shortcut);
          if (it == flag_shortcuts.end()) {
            throw ParseException(std::string("Unknown flag -") + shortcut);
          }
          if (!flags.insert(it->second).second) {
            throw ParseException("Repeated flag --" + it->second);
          }
        }
      }
    }
  }
}

bool CLI::CLI::has_flag(const std::string &full_name) {
  return flags.find(full_name) != flags.end();
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
