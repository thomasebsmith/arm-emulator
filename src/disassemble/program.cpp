#include <iostream>
#include "program.h"


namespace Disassemble {
  void Program::add_instruction(InstructionType inst) {
    instructions.emplace_back(inst);
  }

  void Program::print_to(std::ostream &out) const {
    for (const auto &inst : instructions) {
      inst.print_to(out);
      out << '\n';
    }
  }
}
