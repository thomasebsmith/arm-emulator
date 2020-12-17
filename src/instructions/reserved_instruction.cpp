#include <iostream>
#include "decode_exception.h"
#include "reserved_instruction.h"
#include "utils/bit_utils.h"

using Utils::BitUtils::extract_bits;

namespace Instructions {
  ReservedInstruction::ReservedInstruction(
    IntegerType inst
  ) {
    const unsigned op0_offset = 29;
    const unsigned op1_offset = 16;
    auto op0 = inst >> op0_offset;
    auto op1 = (inst >> op1_offset) & 0b111111111;
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
