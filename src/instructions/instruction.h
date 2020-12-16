#ifndef __SRC_INSTRUCTIONS_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_INSTRUCTION_H__

#include <cstdint>
#include <iostream>

namespace Instructions {
  class Instruction {
  public:
    using IntegerType = uint32_t;
    Instruction(IntegerType inst);

    void print_to(std::ostream &out) const;
  };
}

#endif
