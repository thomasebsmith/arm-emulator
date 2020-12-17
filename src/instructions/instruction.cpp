#include <cassert>
#include <iostream>
#include <variant>
#include "decode_exception.h"
#include "instruction.h"
#include "shared.h"
#include "utils/bit_utils.h"

using Utils::BitUtils::extract_bits;

namespace Instructions {
  Instruction::Instruction(IntegerType inst):
    internal_instruction{decode(inst)} {}

  Instruction::InternalInstructionT Instruction::decode(IntegerType inst) {
    IntegerType opcode;
    std::tie(opcode, std::ignore) = extract_bits(inst, 25u, 29u);
    switch (opcode) {
      case 0b0000:
        return ReservedInstruction(inst);
      case 0b0001:
        throw DecodeException("Unallocated opcode 0001");
      case 0b0010:
        return SVEInstruction(inst);
      case 0b0011:
        throw DecodeException("Unallocated opcode 0011");
      case 0b1000:
      case 0b1001:
        return DataProcessingImmediateInstruction(inst);
      case 0b1010:
      case 0b1011:
        return BranchExceptionOrSystemInstruction(inst);
      case 0b0100:
      case 0b0110:
      case 0b1100:
      case 0b1110:
        return LoadOrStoreInstruction(inst);
      case 0b0101:
      case 0b1101:
        return DataProcessingRegisterInstruction(inst);
      case 0b0111:
      case 0b1111:
        return DataProcessingAdvancedInstruction(inst);
      default:
        assert(false && "Unhandled switch case in instruction decoder");
    }
  }

  void Instruction::print_to(std::ostream &out) const {
    std::visit([&out](const auto &inst) {
      inst.print_to(out);
    }, internal_instruction);
  }
}
