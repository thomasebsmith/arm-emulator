#include <optional>
#include <stdexcept>
#include <string>
#include <vector>
#include "test.h"

Test::FailedAssertion::FailedAssertion(const std::string &msg):
  std::runtime_error{msg} {}

Test::Failure::Failure(
  const std::string &reason_in,
  const std::vector<std::string> &test_stack_trace_in
) {}

Test::Test(
  const std::string &description_in,
  const std::function<void()> &run_test_in
): description{description_in}, run_test{run_test_in} {}

void Test::assert(bool value, const std::string &failure_message) {
  if (!value) {
    throw FailedAssertion(failure_message);
  }
}

Test::Result Test::run() {
  try {
    run_test();
  }
  catch (const FailedAssertion &failure) {
    return {"Assertion failed: " + std::string{failure.what()}, {description}};
  }
  catch (const std::runtime_error &error) {
    return {error.what(), {description}};
  }
  return std::nullopt;
}
