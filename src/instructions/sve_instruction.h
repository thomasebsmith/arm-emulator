#ifndef __SRC_INSTRUCTIONS_SVE_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_SVE_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  class SVEInstruction {
  public:
    SVEInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  };
}

#endif
