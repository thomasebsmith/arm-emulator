#ifndef __SRC_DISASSEMBLE_PROGRAM_H__
#define __SRC_DISASSEMBLE_PROGRAM_H__

#include <iostream>
#include <vector>
#include "instructions/instruction.h"

namespace Disassemble {
  class Program {
  public:
    using Instruction = Instructions::Instruction;
    using InstructionType = Instruction::IntegerType;

    void add_instruction(InstructionType inst);

    void print_to(std::ostream &out) const;
  private:
    std::vector<Instruction> instructions;
  };
}

#endif
