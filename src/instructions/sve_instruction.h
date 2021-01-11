#ifndef __SRC_INSTRUCTIONS_SVE_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_SVE_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  /*
   * Represents an ARM instruction that performs a scalable vector extension
   * instruction.
   */
  class SVEInstruction {
  public:
    /*
     * Parses an instruction from the binary data in inst. Requires that inst
     * represents an instruction of the appropriate category.
     */
    SVEInstruction(IntegerType inst);

    /*
     * Outputs a human-readable (disassembled) form of the instruction to out.
     */
    void print_to(std::ostream &out) const;
  };
}

#endif
