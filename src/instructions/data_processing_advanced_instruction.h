#ifndef SRC_INSTRUCTIONS_DATA_PROCESSING_ADVANCED_INSTRUCTION_H
#define SRC_INSTRUCTIONS_DATA_PROCESSING_ADVANCED_INSTRUCTION_H

#include <iostream>
#include "shared.h"

namespace Instructions {
  /*
   * Represents an ARM instruction that performs an advanced data-processing
   * operation.
   */
  class DataProcessingAdvancedInstruction {
  public:
    /*
     * Parses an instruction from the binary data in inst. Requires that inst
     * represents an instruction of the appropriate category.
     */
    DataProcessingAdvancedInstruction(IntegerType inst);

    /*
     * Outputs a human-readable (disassembled) form of the instruction to out.
     */
    void print_to(std::ostream &out) const;
  };
}

#endif
