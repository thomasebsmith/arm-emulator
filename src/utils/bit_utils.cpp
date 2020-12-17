#include "bit_utils.h"

namespace Utils::BitUtils {
  bool is_correct_endianness() {
    // The "correct" endianness is little-endian.
    // This check works if number < 256.
    unsigned number = 1;
    return *reinterpret_cast<char *>(&number) == number;
  }
}
