#ifndef SRC_INSTRUCTIONS_BRANCH_EXCEPTION_OR_SYSTEM_INSTRUCTION_H
#define SRC_INSTRUCTIONS_BRANCH_EXCEPTION_OR_SYSTEM_INSTRUCTION_H

#include <iostream>
#include "shared.h"

namespace Instructions {
  /*
   * Represents an ARM instruction that performs a branch, is exeception-
   * related, or is system-related.
   */
  class BranchExceptionOrSystemInstruction {
  public:
    /*
     * Parses an instruction from the binary data in inst. Requires that inst
     * represents an instruction of the appropriate category.
     */
    BranchExceptionOrSystemInstruction(IntegerType inst);

    /*
     * Outputs a human-readable (disassembled) form of the instruction to out.
     */
    void print_to(std::ostream &out) const;
  };
}

#endif
