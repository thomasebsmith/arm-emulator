#include <iostream>
#include "disassemble/disassembler.h"
#include "disassemble.h"

using Disassemble::Disassembler;

int disassemble(std::istream &in, std::ostream &out, std::ostream &out_err) {
  try {
    Disassembler disassembler{in};
    out << disassembler;
    return 0;
  }
  catch (Disassembler::ParseException &err) {
    out_err << err.what() << '\n';
    return 1;
  }
}
