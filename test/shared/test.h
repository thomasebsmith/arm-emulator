#ifndef __TEST_SHARED_TEST_H__
#define __TEST_SHARED_TEST_H__

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

class Test {
public:
  class FailedAssertion: std::runtime_error {
  public:
    FailedAssertion(const std::string &msg);
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

  static void assert(bool value, const std::string &failure_message);

  Result run();

private:
  std::string description;
  std::function<void()> run_test;
};

#endif
