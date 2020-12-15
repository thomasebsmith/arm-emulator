#include <iostream>
#include <stdexcept>
#include "disassembler.h"


namespace Disassemble {
  Disassembler::Disassembler(std::istream &machine_code): in{machine_code} {}

  void Disassembler::print_to(std::ostream &out) {
    out << "TODO: Disassemble machine code\n";
    std::string line;
    while (std::getline(in, line)) {
      out << line << '\n';
    }
  }

  Disassembler::ParseException::ParseException(
    const std::string &error_message
  ): std::runtime_error{error_message} {}

  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler) {
    disassembler.print_to(out);
    return out;
  }
}

