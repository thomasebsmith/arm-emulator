#ifndef __SRC_DISASSEMBLER_DISASSEMBLER_H__
#define __SRC_DISASSEMBLER_DISASSEMBLER_H__

#include <iostream>
#include <stdexcept>
#include <string>
#include "instructions/decode_exception.h"
#include "program.h"

namespace Disassemble {
  class Disassembler {
  public:
    Disassembler(std::istream &machine_code);

    void print_to(std::ostream &out);

    using DecodeException = Instructions::DecodeException;

    class ParseException: public std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };
  private:
    std::istream &in;
    Program program;
  };

  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler);
}

#endif
