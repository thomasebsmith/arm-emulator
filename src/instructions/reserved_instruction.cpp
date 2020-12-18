#include <iostream>
#include "decode_exception.h"
#include "reserved_instruction.h"
#include "utils/bit_utils.h"

using Utils::BitUtils::extract_bits;

namespace Instructions {
  ReservedInstruction::ReservedInstruction(
    IntegerType inst
  ) {
    const auto [op1, _, op0] = extract_bits(inst, 16u, 25u, 29u);
    if (op0 == 0b000 && op1 == 0b000000000) {
      type = Type::UDF;
    }
    else {
      throw DecodeException{"Unallocated instruction of type 'reserved'"};
    }
  }

  void ReservedInstruction::print_to(std::ostream &out) const {
    out << "TODO: Reserved instruction";
  }
}
