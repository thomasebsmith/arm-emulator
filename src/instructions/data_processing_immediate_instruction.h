#ifndef SRC_INSTRUCTIONS_DATA_PROCESSING_IMMEDIATE_INSTRUCTION_H
#define SRC_INSTRUCTIONS_DATA_PROCESSING_IMMEDIATE_INSTRUCTION_H

#include <iostream>
#include "shared.h"

namespace Instructions {
  /*
   * Represents an ARM instruction that performs a data-processing instruction
   * involving an immediate (literal) value.
   */
  class DataProcessingImmediateInstruction {
  public:
    /*
     * Parses an instruction from the binary data in inst. Requires that inst
     * represents an instruction of the appropriate category.
     */
    DataProcessingImmediateInstruction(IntegerType inst);

    /*
     * Outputs a human-readable (disassembled) form of the instruction to out.
     */
    void print_to(std::ostream &out) const;
  };
}

#endif
