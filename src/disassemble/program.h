#ifndef SRC_DISASSEMBLE_PROGRAM_H
#define SRC_DISASSEMBLE_PROGRAM_H

#include <iostream>
#include <vector>
#include "instructions/instruction.h"
#include "instructions/shared.h"

namespace Disassemble {
  /*
   * Represents a series of ARM instructions.
   * Initially, it is empty.
   */
  class Program {
  public:
    using Instruction = Instructions::Instruction;
    using InstructionType = Instructions::IntegerType;

    /*
     * Appends inst to this Program. inst should be an ARM instruction, encoded
     * in its binary machine code form.
     */
    void add_instruction(InstructionType inst);

    /*
     * Prints disassembly for all instructions in this Program to out.
     */
    void print_to(std::ostream &out) const;
  private:
    std::vector<Instruction> instructions;
  };
}

#endif
