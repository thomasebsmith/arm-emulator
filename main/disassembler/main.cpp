#include <iostream>
#include "meta/program_info.h"

int main(int argc, char *argv[]) {
  std::cout << Meta::ProgramInfo::show_version_info;
  return 0;
}
