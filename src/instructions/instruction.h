#ifndef __SRC_INSTRUCTIONS_INSTRUCTION_H__
#define __SRC_INSTRUCTIONS_INSTRUCTION_H__

#include <iostream>
#include <variant>
#include "branch_exception_or_system_instruction.h"
#include "data_processing_immediate_instruction.h"
#include "data_processing_register_instruction.h"
#include "data_processing_advanced_instruction.h"
#include "load_or_store_instruction.h"
#include "reserved_instruction.h"
#include "shared.h"
#include "sve_instruction.h"

namespace Instructions {
  class Instruction {
  public:
    Instruction(IntegerType inst);

    void print_to(std::ostream &out) const;
  private:
    using InternalInstructionT = std::variant<
      BranchExceptionOrSystemInstruction,
      DataProcessingImmediateInstruction,
      DataProcessingRegisterInstruction,
      DataProcessingAdvancedInstruction,
      LoadOrStoreInstruction,
      ReservedInstruction,
      SVEInstruction
    >;

    InternalInstructionT internal_instruction;

    InternalInstructionT decode(IntegerType inst);
  };
}

#endif
