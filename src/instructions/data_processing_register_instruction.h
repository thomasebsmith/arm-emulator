#ifndef __SRC_INSTRUCTIONS_DATA_PROCESSING_REGISTER_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_DATA_PROCESSING_REGISTER_INSTRUCTION_H__

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
