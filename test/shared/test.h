#ifndef TEST_SHARED_TEST_H
#define TEST_SHARED_TEST_H

#include <cstdint>
#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class Test {
public:
  class FailedAssertion: public std::runtime_error {
  public:
    FailedAssertion(const std::string &msg);
    FailedAssertion(const std::string &msg, const std::string &location);
    const std::optional<std::string> &get_location() const;
  private:
    std::optional<std::string> failure_location;
  };

  struct Failure {
    Failure(
      const std::string &reason_in,
      const std::vector<std::string> &test_stack_trace_in
    );
    std::string reason;
    std::vector<std::string> test_stack_trace;
  };

  using Result = std::optional<Failure>;

  Test(
    const std::string &description_in,
    const std::function<void()> &run_test_in
  );

  static void assert_true(bool value, const std::string &failure_message);
  static void assert_true(
    bool value,
    const std::string &failure_message,
    const std::string &function_name,
    uint64_t line_number,
    const std::string &file_name
  );

  Result run();

private:
  std::string description;
  std::function<void()> run_test;
};

#define confirm(value, msg) \
  Test::assert_true((value), (msg), __func__, __LINE__, __FILE__)

#endif
