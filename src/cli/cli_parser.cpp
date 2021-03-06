#include <cassert>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <variant>
#include <vector>
#include "cli/cli_parser.h"


template <typename T>
constexpr bool false_v = false;

CLI::CLIParser::ParseException::ParseException(
  const std::string &error_message
):
  std::runtime_error{error_message}
{}

CLI::CLIParser::CLIParser(
  int argc,
  char *argv[],
  const std::vector<Option> &options
) {
  if (argc == 0) {
    throw ParseException("No program name given");
  }

  program_name = argv[0];

  // Parse options into internal data structures. Throw a
  //  ParseException if there are repeated options, arguments, etc.
  for (const auto &option_variant : options) {
    std::visit([this](auto &&option) {
      using OptionT = std::decay_t<decltype(option)>;

      if constexpr (std::is_same_v<OptionT, Argument>) {
        if (!possible_arguments.insert({
            option.internal_name,
            {option, possible_arguments.size()}
          }).second) {
          throw ParseException("Repeated argument " + option.internal_name);
        }
      }
      else if constexpr (
        std::is_same_v<OptionT, Flag> ||
        std::is_same_v<OptionT, NamedArgument>
      ) {
        if (!possible_named_args_and_flags.insert({
              option.full_name,
              NamedArgOrFlag(option)
            }).second) {
          throw ParseException("Repeated option " + option.full_name);
        }
        if (!shortcuts.insert({option.shortcut, option.full_name}).second) {
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

  // Parse the actual provided arguments. Throw a ParseException if any of
  // these are invalid or unexpected.
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

      std::string option_name;

      if (argument[1] == '-') {
        // Option begins with --
        assert(argument.length() > 2);
        option_name = argument.substr(2);
      }
      else {
        // Option begins with -
        for (size_t j = 1; j < argument.length(); ++j) {
          char shortcut = argument[j];
          auto it = shortcuts.find(shortcut);
          if (it == shortcuts.end()) {
            throw ParseException(std::string("Unknown option -") + shortcut);
          }
          option_name = it->second;
        }
      }

      auto it = possible_named_args_and_flags.find(option_name);
      if (it == possible_named_args_and_flags.end()) {
        throw ParseException("Unknown option " + argument);
      }

      std::visit([&](auto &&option) {
        using OptionT = std::decay_t<decltype(option)>;

        if constexpr (std::is_same_v<OptionT, Flag>) {
          // Handle a flag
          if (!flags.emplace(std::move(option_name)).second) {
            throw ParseException("Repeated flag " + argument);
          }
        } else if constexpr (std::is_same_v<OptionT, NamedArgument>) {
          // Handle a named argument
          ++i;
          if (i >= argc) {
            throw ParseException("No argument given with --" + option_name);
          }

          auto value = argv[i];
          if (!named_arguments.emplace(
                std::move(option_name),
                std::move(value)
              ).second) {
            throw ParseException("Repeated argument " + argument);
          }
        } else {
          static_assert(false_v<OptionT>, "Unexpected CLI option variant");
        }
      }, it->second);
    }
  }
}

bool CLI::CLIParser::has_flag(const std::string &full_name) {
  return flags.find(full_name) != flags.end();
}

std::optional<std::string_view> CLI::CLIParser::get_argument(
  const std::string &internal_name
) {
  auto it = possible_arguments.find(internal_name);
  if (it == possible_arguments.end()) {
    return std::nullopt;
  }
  auto argument_index = it->second.second;
  if (argument_index >= arguments.size()) {
    return std::nullopt;
  }
  return arguments[argument_index];
}

std::ostream &CLI::CLIParser::show_help(std::ostream &out) {
  out << "Usage: " << program_name;
  for (const auto &pair : possible_named_args_and_flags) {
    if (const auto *named_arg = std::get_if<NamedArgument>(&pair.second)) {
      out << " [--" << pair.first << ' ' << named_arg->value_description;
      out << ']';
    } else {
      out << " [--" << pair.first << ']';
    }
  }
  for (const auto &pair : possible_arguments) {
    out << " [" << pair.second.first.help_name << ']';
  }
  out << '\n';
  for (const auto &pair : possible_named_args_and_flags) {
    std::visit([&out](auto &&option) {
      using OptionT = std::decay_t<decltype(option)>;

      out << "\t--" << option.full_name;
      if constexpr (std::is_same_v<OptionT, NamedArgument>) {
        out << ' ' << option.value_description;
      }

      out << ", -" << option.shortcut;
      if constexpr (std::is_same_v<OptionT, NamedArgument>) {
        out << ' ' << option.value_description;
      }
      out << ": ";

      out << option.description << '\n';
    }, pair.second);
  }
  for (const auto &pair : possible_arguments) {
    const auto &argument = pair.second.first;
    out << '\t' << argument.help_name << ": " << argument.description << '\n';
  }
  return out;
}
