#ifndef TEST_SHARED_TEST_FRAMEWORK_H
#define TEST_SHARED_TEST_FRAMEWORK_H

#include <functional>
#include <string>
#include <vector>
#include "test.h"

class TestFramework {
public:
  TestFramework(const std::string &description_in);

  void that(
    const std::string &description,
    const std::function<void()> &run_test
  );

  void include(TestFramework &&otherFramework);

  std::vector<Test::Result> run_all();

private:
  std::string description;
  std::vector<TestFramework> sub_frameworks;
  std::vector<Test> tests;
};

#endif
