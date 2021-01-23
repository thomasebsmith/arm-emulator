#include <iostream>
#include <stdexcept>
#include "disassembler.h"
#include "program.h"
#include "utils/bit_utils.h"


namespace Disassemble {
  Disassembler::Disassembler(std::istream &machine_code): in{machine_code} {}

  void Disassembler::print_to(std::ostream &out) {
    // Read the raw bytes of each instruction into inst.
    // Then, add inst to a program.
    // Finally, print the entire program.
    Program::InstructionType inst;
    while (in.read(
      reinterpret_cast<char *>(&inst),
      sizeof(Program::InstructionType)
    )) {
      inst = Utils::BitUtils::convert_endianness(inst);
      program.add_instruction(inst);
    }
    program.print_to(out);
  }

  // ParseException is just a wrapper for std::runtime_error.
  Disassembler::ParseException::ParseException(
    const std::string &error_message
  ): std::runtime_error{error_message} {}

  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler) {
    disassembler.print_to(out);
    return out;
  }
}

