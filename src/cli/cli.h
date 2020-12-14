#ifndef __SRC_CLI_CLI_H__
#define __SRC_CLI_CLI_H__

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

namespace CLI {
  class CLI {
  public:

    struct Argument {
      const std::string internal_name;
      const std::string help_name;
      const std::string description;

      Argument() = delete;
    };

    struct Flag {
      char shortcut;
      const std::string full_name;
      const std::string description;

      Flag() = delete;
    };

    class ParseException: public std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };

    using Option = std::variant<Argument, Flag>;

    CLI(int argc, char *argv[], const std::vector<Option> &options);

    bool has_flag(const std::string &full_name);

    std::optional<std::string_view> get_argument(
      const std::string_view internal_name
    );

    std::ostream &show_help(std::ostream &out);

  private:
    std::vector<Argument> possible_arguments;
    std::unordered_map<char, std::string> flag_shortcuts;
    std::unordered_map<std::string, Flag> possible_flags;
    std::string program_name;
    std::vector<std::string> arguments;
    std::unordered_set<std::string> flags;
  };
};

#endif
