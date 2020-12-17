#ifndef __SRC_INSTRUCTIONS_DECODE_EXCEPTION_H__
#define __SRC_INSTRUCTIONS_DECODE_EXCEPTION_H__

#include <stdexcept>
#include <string>

namespace Instructions {
  class DecodeException: public std::runtime_error {
  public:
    DecodeException(const std::string &error_message);
  };
}

#endif
