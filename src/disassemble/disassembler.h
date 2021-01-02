#ifndef __SRC_DISASSEMBLER_DISASSEMBLER_H__
#define __SRC_DISASSEMBLER_DISASSEMBLER_H__

#include <iostream>
#include <stdexcept>
#include <string>
#include "instructions/decode_exception.h"
#include "program.h"

namespace Disassemble {
  /*
   * Represents some machine code that is in the process of being disassembled.
   */
  class Disassembler {
  public:

    /*
     * Disassembles the machine code found in machine_code. machine_code is
     * read as binary data.
     *
     * May throw a ParseException.
     */
    Disassembler(std::istream &machine_code);

    /*
     * Prints a human-readable, disassembled version of the machine code to
     * out.
     */
    void print_to(std::ostream &out);

    using DecodeException = Instructions::DecodeException;

    /*
     * Represents an error that occurs while parsing the machine code.
     */
    class ParseException: public std::runtime_error {
    public:
      ParseException(const std::string &error_message);
    };
  private:
    std::istream &in;
    Program program;
  };

  /*
   * Equivalent to disassembler.print_to(out).
   */
  std::ostream &operator<<(std::ostream &out, Disassembler &disassembler);
}

#endif
