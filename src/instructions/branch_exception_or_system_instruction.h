#ifndef __SRC_INSTRUCTIONS_BRANCH_EXCEPTION_OR_SYSTEM_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_BRANCH_EXCEPTION_OR_SYSTEM_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  class BranchExceptionOrSystemInstruction {
  public:
    BranchExceptionOrSystemInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  };
}

#endif
