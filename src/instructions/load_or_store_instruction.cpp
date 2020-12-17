#include <iostream>
#include "load_or_store_instruction.h"

namespace Instructions {
  LoadOrStoreInstruction::LoadOrStoreInstruction(
    IntegerType inst
  ) {}

  void LoadOrStoreInstruction::print_to(std::ostream &out) const {
    out << "TODO: Load or store instruction";
  }
}
