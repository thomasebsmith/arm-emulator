#ifndef SRC_INSTRUCTIONS_DATA_PROCESSING_REGISTER_INSTRUCTION_H
#define SRC_INSTRUCTIONS_DATA_PROCESSING_REGISTER_INSTRUCTION_H

#include <iostream>
#include "shared.h"

namespace Instructions {
  class DataProcessingRegisterInstruction {
  public:
    DataProcessingRegisterInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  };
}

#endif
