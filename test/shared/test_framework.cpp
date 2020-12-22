#include <functional>
#include <string>
#include "test_framework.h"

TestFramework::FailedAssertion::FailedAssertion(const std::string &msg):
  std::runtime_error{msg} {}

void TestFramework::that(
  const std::string &description,
  const std::function<void()> &run_test
) {
  tests.emplace_back(description, run_test);
}

void TestFramework::include(TestFramework &&otherFramework) {
  subFrameworks.emplace_back(otherFramework);
}

void TestFramework::assert(bool value, const std::string &failure_message) {
  if (!value) {
    throw FailedAssertion(failure_message);
  }
}
