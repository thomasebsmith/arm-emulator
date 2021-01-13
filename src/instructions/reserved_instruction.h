#ifndef SRC_INSTRUCTIONS_RESERVED_INSTRUCTION_H
#define SRC_INSTRUCTIONS_RESERVED_INSTRUCTION_H

#include <iostream>
#include "shared.h"

namespace Instructions {
  /*
   * Represents an ARM instruction that is reserved. Such an instruction does
   * not perform a valid operation (the only valid instruction within this
   * class is UDF).
   */
  class ReservedInstruction {
  public:
    /*
     * Parses an instruction from the binary data in inst. Requires that inst
     * represents an instruction of the appropriate category.
     */
    ReservedInstruction(IntegerType inst);

    /*
     * Outputs a human-readable (disassembled) form of the instruction to out.
     */
    void print_to(std::ostream &out) const;
  private:
    enum class Type {
      UDF
    };
    Type type;

    ImmediateType immediate;
  };
}

#endif
