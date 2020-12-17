#include <stdexcept>
#include <string>
#include "decode_exception.h"

namespace Instructions {
  DecodeException::DecodeException(const std::string &error_message):
    std::runtime_error{error_message} {}
}
