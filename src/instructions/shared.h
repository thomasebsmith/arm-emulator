#ifndef SRC_INSTRUCTIONS_SHARED_H
#define SRC_INSTRUCTIONS_SHARED_H

#include <cstdint>

namespace Instructions {
  // IntegerType designates the type of integer that holds exactly one ARM
  // instruction.
  using IntegerType = uint32_t;

  // ImmediateType designates the type of integer that holds exactly one ARM
  // immediate value (part of certain instructions).
  using ImmediateType = uint16_t;
}

#endif
