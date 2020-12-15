#ifndef __SRC_DISASSEMBLER_DISASSEMBLER_H__
#define __SRC_DISASSEMBLER_DISASSEMBLER_H__

#include <iostream>
#include <stdexcept>
#include <string>

namespace Disassemble {
  class Disassembler {
  public:
    Disassembler(std::istream &machine_code);

    void print_to(std::ostream &out);

    class ParseException: public std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };
  private:
    std::istream &in;
  };

  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler);
}

#endif
