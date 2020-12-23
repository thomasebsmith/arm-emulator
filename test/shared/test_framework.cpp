#include <functional>
#include <string>
#include <utility>
#include <vector>
#include "test_framework.h"

TestFramework::TestFramework(const std::string &description_in):
  description{description_in} {}

void TestFramework::that(
  const std::string &description,
  const std::function<void()> &run_test
) {
  tests.emplace_back(description, run_test);
}

void TestFramework::include(TestFramework &&otherFramework) {
  sub_frameworks.emplace_back(otherFramework);
}

std::vector<Test::Result> TestFramework::run_all() {
  std::vector<Test::Result> results;
  for (auto &framework : sub_frameworks) {
    auto framework_results = framework.run_all();
    for (auto &result : framework_results) {
      if (result) {
        result->test_stack_trace.push_back("In " + description);
      }
      results.push_back(std::move(result));
    }
  }
  for (auto &test : tests) {
   auto result = test.run();
   if (result) {
    result->test_stack_trace.push_back("In " + description);
   }
   results.push_back(std::move(result));
  }
  return results;
}
