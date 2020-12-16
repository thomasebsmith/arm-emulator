#include <iostream>
#include <stdexcept>
#include "disassembler.h"
#include "program.h"


namespace Disassemble {
  Disassembler::Disassembler(std::istream &machine_code): in{machine_code} {}

  void Disassembler::print_to(std::ostream &out) {
    Program::InstructionType inst;
    while (in.read(
      reinterpret_cast<char *>(&inst),
      sizeof(Program::InstructionType)
    )) {
      program.add_instruction(inst);
    }
    program.print_to(out);
  }

  Disassembler::ParseException::ParseException(
    const std::string &error_message
  ): std::runtime_error{error_message} {}

  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler) {
    disassembler.print_to(out);
    return out;
  }
}

