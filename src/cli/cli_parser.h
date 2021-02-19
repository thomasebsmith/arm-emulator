#ifndef __SRC_CLI_CLI_PARSER_H__
#define __SRC_CLI_CLI_PARSER_H__

#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <variant>
#include <vector>

namespace CLI {
  /*
   * Represents a set of parsed command line flags and arguments for some
   * program.
   */
  class CLIParser {
  public:

    /*
     * An Argument is a value given at the command line without a name.
     * For example, in "vim ~/.vimrc", "~/.vimrc" is an argument.
     *
     * internal_name is used when accessing the argument's value with
     * get_argument.
     *
     * help_name and description are used in show_help.
     */
    struct Argument {
      std::string internal_name;
      std::string help_name;
      std::string description;

      Argument() = delete;
    };

    /*
     * A Flag is a boolean switch given at the command line by name or in
     * an abbreviated (one-letter) form.
     * For example, in "ls -l", "-l" is a flag.
     *
     * shortcut is the one-letter form (e.g. 'l' for "-l").
     * full_name is the full form of the flag, with leading dashes
     * removed(e.g. "all" for "--all").
     *
     * description is used in show_help.
     */
    struct Flag {
      char shortcut;
      std::string full_name;
      std::string description;

      Flag() = delete;
    };

    struct NamedArgument {
      char shortcut;
      std::string full_name;
      std::string description;
      std::string value_description;

      NamedArgument() = delete;
    };

    /*
     * Represents an error that occurs while parsing command line arguments.
     */
    class ParseException: public std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };

    /*
     * A utility typedef for any kind of command line option.
     */
    using Option = std::variant<Argument, Flag, NamedArgument>;

    /*
     * Parse the command line arguments found in argc and argv using the
     * possible valid options in options.
     *
     * Requires length(argv) >= argc.
     */
    CLIParser(int argc, char *argv[], const std::vector<Option> &options);

    /*
     * Returns whether the flag with name full_name was found while parsing.
     */
    bool has_flag(const std::string &full_name);

    /*
     * Returns the value found for the argument with name internal_name, or
     * nullopt if the argument was not supplied.
     */
    std::optional<std::string_view> get_argument(
      const std::string &internal_name
    );

    /*
     * Returns the value found for the argument with name full_name, or
     * nullopt if the named argument was not supplied.
     */
    std::optional<std::string_view> get_named_argument(
      const std::string &full_name
    );

    /*
     * Prints the help for this CLI to out.
     */
    std::ostream &show_help(std::ostream &out);

  private:
    using NamedArgOrFlag = std::variant<NamedArgument, Flag>;

    std::map<std::string, std::pair<Argument, size_t>> possible_arguments;
    std::map<std::string, NamedArgOrFlag> possible_named_args_and_flags;
    std::unordered_map<char, std::string> shortcuts;

    std::string program_name;
    std::vector<std::string> arguments;
    std::unordered_map<std::string, std::string> named_arguments;
    std::unordered_set<std::string> flags;
  };
}

#endif
