#include "cpu/exec.h"
#include "all-instr.h"

static OpcodeEntry load_table [8] = {
  EXW(ld,1), EXW(ld,2), EXW(ld, 4),EMPTY, EXW(ld,1), EXW(ld,2), EMPTY,EMPTY
};

static make_EHelper(load) {
  decinfo.width = load_table[decinfo.isa.instr.funct3].width;
  idex(pc, &load_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry store_table [8] = {
  EXW(st,1), EXW(st,2), EXW(st, 4), EMPTY, EXW(st,1), EXW(st,2), EMPTY, EMPTY
};

static make_EHelper(store) {
  decinfo.width = store_table[decinfo.isa.instr.funct3].width;
  idex(pc, &store_table[decinfo.isa.instr.funct3]);
}

static OpcodeEntry opcode_table [32] = {
  /* b00 */ IDEX(ld, load), EMPTY, EMPTY, EMPTY, IDEX(RI,ri), IDEX(AUIPC,aui), EMPTY, EMPTY,
  /* b01 */ IDEX(st, store), EMPTY, EMPTY, EMPTY, IDEX(R,r), IDEX(U, lui), EMPTY, EMPTY,
  /* b10 */ EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY,
  /* b11 */ IDEX(B,b), IDEX(JALR,jr), EX(nemu_trap), IDEX(JAL,j), IDEX(ECALL,ec), EMPTY, EMPTY, EMPTY,
};

void isa_exec(vaddr_t *pc) {
  decinfo.isa.instr.val = instr_fetch(pc, 4);
  assert(decinfo.isa.instr.opcode1_0 == 0x3);
  idex(pc, &opcode_table[decinfo.isa.instr.opcode6_2]);
}
