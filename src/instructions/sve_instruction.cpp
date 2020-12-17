#include <iostream>
#include "sve_instruction.h"

namespace Instructions {
  SVEInstruction::SVEInstruction(
    IntegerType inst
  ) {}

  void SVEInstruction::print_to(std::ostream &out) const {
    out << "TODO: SVE instruction";
  }
}
