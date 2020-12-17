#include <iostream>
#include "reserved_instruction.h"

namespace Instructions {
  ReservedInstruction::ReservedInstruction(
    IntegerType inst
  ) {}

  void ReservedInstruction::print_to(std::ostream &out) const {
    out << "TODO: Reserved instruction";
  }
}
