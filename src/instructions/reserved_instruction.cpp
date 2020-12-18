#include <iostream>
#include "decode_exception.h"
#include "reserved_instruction.h"
#include "utils/bit_utils.h"

using Utils::BitUtils::extract_bits;

namespace Instructions {
  ReservedInstruction::ReservedInstruction(
    IntegerType inst
  ) {
    const auto [imm16, op1, _, op0] = extract_bits(inst, 0u, 16u, 25u, 29u);
    if (op0 == 0b000 && op1 == 0b000000000) {
      type = Type::UDF;
      immediate = static_cast<ImmediateType>(imm16);
    }
    else {
      throw DecodeException{"Unallocated instruction of type 'reserved'"};
    }
  }

  void ReservedInstruction::print_to(std::ostream &out) const {
    switch (type) {
      case Type::UDF:
        out << "UDF #" << immediate;
        break;
      default:
        assert(false && "Switch statement does not cover all types");
    }
  }
}
