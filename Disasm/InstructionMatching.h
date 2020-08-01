#ifndef JAK_DISASSEMBLER_INSTRUCTIONMATCHING_H
#define JAK_DISASSEMBLER_INSTRUCTIONMATCHING_H

#include "Instruction.h"

template <typename T>
struct MatchParam {
  MatchParam() { is_wildcard = true; }

  MatchParam(T x) {
    value = x;
    is_wildcard = false;
  }

  T value;
  bool is_wildcard = true;

  bool operator==(const T& other) { return is_wildcard || (value == other); }
  bool operator!=(const T& other) { return !(*this == other); }
};

bool is_no_link_instr(const Instruction& instr, MatchParam<InstructionKind> kind);
bool is_no_link_gpr_store(const Instruction& instr,
                          MatchParam<int> size,
                          MatchParam<Register> src,
                          MatchParam<int> offset,
                          MatchParam<Register> dest);
bool is_no_link_gpr_load(const Instruction& instr,
                         MatchParam<int> size,
                         MatchParam<bool> is_signed,
                         MatchParam<Register> dst_reg,
                         MatchParam<int> offset,
                         MatchParam<Register> mem_reg);

bool is_no_link_fpr_store(const Instruction& instr,
                          MatchParam<Register> src,
                          MatchParam<int> offset,
                          MatchParam<Register> dest);
bool is_no_link_fpr_load(const Instruction& instr,
                         MatchParam<Register> dst_reg,
                         MatchParam<int> offset,
                         MatchParam<Register> mem_reg);

bool is_gpr_store(const Instruction& instr);
bool is_gpr_load(const Instruction& instr, MatchParam<bool> is_signed);
int32_t get_gpr_store_offset(const Instruction& instr);

bool is_gpr_3(const Instruction& instr,
              MatchParam<InstructionKind> kind,
              MatchParam<Register> dst,
              MatchParam<Register> src0,
              MatchParam<Register> src1);

bool is_gpr_2_imm(const Instruction& instr,
                  MatchParam<InstructionKind> kind,
                  MatchParam<Register> dst,
                  MatchParam<Register> src,
                  MatchParam<int32_t> imm);

bool is_nop(const Instruction& instr);
bool is_jr_ra(const Instruction& instr);

Register make_gpr(Reg::Gpr gpr);
Register make_fpr(int fpr);

#endif  // JAK_DISASSEMBLER_INSTRUCTIONMATCHING_H
