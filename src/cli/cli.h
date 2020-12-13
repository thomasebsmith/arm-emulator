#ifndef __SRC_CLI_CLI_H__
#define __SRC_CLI_CLI_H__

#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

namespace CLI {
  class CLI {
  public:

    struct Argument {
      const std::string_view internal_name;
      const std::string_view help_name;
      const std::string_view description;

      Argument() = delete;
    };

    struct Flag {
      char shortcut;
      const std::string_view full_name;
      const std::string_view description;

      Flag() = delete;
    };

    class ParseException: std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };

    using Option = std::variant<Argument, Flag>;

    CLI(int argc, char *argv[], const std::vector<Option> &options);

    bool has_flag(const std::string_view full_name);

    std::optional<std::string_view> get_argument(
      const std::string_view internal_name
    );

    std::ostream &show_help(std::ostream &out);

  private:
  };
};

#endif
