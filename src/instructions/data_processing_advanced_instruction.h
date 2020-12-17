#ifndef __SRC_INSTRUCTIONS_DATA_PROCESSING_ADVANCED_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_DATA_PROCESSING_ADVANCED_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  class DataProcessingAdvancedInstruction {
  public:
    DataProcessingAdvancedInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  };
}

#endif
