#include <cstdint>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
#include "test.h"

Test::FailedAssertion::FailedAssertion(const std::string &msg):
  std::runtime_error{msg}, failure_location{std::nullopt} {}

Test::FailedAssertion::FailedAssertion(
  const std::string &msg,
  const std::string &location
): std::runtime_error{msg}, failure_location{location} {}

const std::optional<std::string> &Test::FailedAssertion::get_location() const {
  return failure_location;
}

Test::Failure::Failure(
  const std::string &reason_in,
  const std::vector<std::string> &test_stack_trace_in
): reason{reason_in}, test_stack_trace{test_stack_trace_in} {}

Test::Test(
  const std::string &description_in,
  const std::function<void()> &run_test_in
): description{description_in}, run_test{run_test_in} {}

void Test::assert_true(bool value, const std::string &failure_message) {
  if (!value) {
    throw FailedAssertion(failure_message);
  }
}

void Test::assert_true(
  bool value,
  const std::string &failure_message,
  const std::string &function_name,
  uint64_t line_number,
  const std::string &file_name
) {
  if (!value) {
    throw FailedAssertion{
      failure_message,
      "At " + file_name + ":" + std::to_string(line_number) +
        " (" + function_name + ")"
    };
  }
}

Test::Result Test::run() {
  try {
    run_test();
  }
  catch (const FailedAssertion &failure) {
    const auto &location = failure.get_location();
    std::vector<std::string> stack_trace;
    if (location) {
      stack_trace.push_back(*location);
    }
    stack_trace.push_back("While testing that " + description);
    return Failure{
      "Assertion failed: " + std::string{failure.what()}, 
      std::move(stack_trace)
    };
  }
  catch (const std::runtime_error &error) {
    return Failure{error.what(), {description}};
  }
  return std::nullopt;
}
