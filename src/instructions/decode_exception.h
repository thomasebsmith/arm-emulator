#ifndef SRC_INSTRUCTIONS_DECODE_EXCEPTION_H
#define SRC_INSTRUCTIONS_DECODE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace Instructions {
  /*
   * Represents an error that occurs while decoding instructions from machine
   * code.
   */
  class DecodeException: public std::runtime_error {
  public:
    /*
     * Creates a DecodeException with the given error message.
     */
    DecodeException(const std::string &error_message);
  };
}

#endif
