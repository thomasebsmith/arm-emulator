#include <iostream>
#include "branch_exception_or_system_instruction.h"

namespace Instructions {
  BranchExceptionOrSystemInstruction::BranchExceptionOrSystemInstruction(
    IntegerType inst
  ) {}

  void BranchExceptionOrSystemInstruction::print_to(std::ostream &out) const {
    out << "TODO: Branch, exception, or system instruction";
  }
}
