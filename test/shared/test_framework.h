#ifndef __TEST_SHARED_TEST_FRAMEWORK_H__
#define __TEST_SHARED_TEST_FRAMEWORK_H__

#include <functional>
#include <stdexcept>
#include <string>
#include <vector>

// TODO: Test.h

class TestFramework {
public:
  class FailedAssertion: std::runtime_error {
  public:
    FailedAssertion(const std::string &msg);
  };

  void that(
    const std::string &description,
    const std::function<void()> &run_test
  );

  void include(TestFramework &&otherFramework);

  static void assert(bool value, const std::string &failure_message);

private:
  std::vector<TestFramework> subFrameworks;
  std::vector<Test> tests;
}

#endif
