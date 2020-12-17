#ifndef __SRC_INSTRUCTIONS_LOAD_OR_STORE_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_LOAD_OR_STORE_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  class LoadOrStoreInstruction {
  public:
    LoadOrStoreInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  };
}

#endif
