#ifndef __SRC_INSTRUCTIONS_RESERVED_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_RESERVED_INSTRUCTION_H__

#include <iostream>
#include "shared.h"

namespace Instructions {
  class ReservedInstruction {
  public:
    ReservedInstruction(IntegerType inst);
    void print_to(std::ostream &out) const;
  private:
    enum class Type {
      UDF
    };
    Type type;
  };
}

#endif
