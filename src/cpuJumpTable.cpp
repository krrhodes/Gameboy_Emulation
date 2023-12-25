#include "cpuJumpTable.h"

int Emulator::ExecuteNextOpcode() {
  int res = 0;
  BYTE opcode = ReadMemory(m_ProgramCounter);
  m_ProgramCounter++;
  res = ExecuteOpcode(opcode);
  return res;
}

int Emulator::ExecuteOpcode(BYTE opcode) {
  switch (opcode) {
  // no-op
  case 0x00:
    return 4;

  // 8-Bit Loads
  case 0x06:
    return CPU_8BIT_LOAD(m_RegisterBC.hi);
  case 0x0E:
    return CPU_8BIT_LOAD(m_RegisterBC.lo);
  case 0x16:
    return CPU_8BIT_LOAD(m_RegisterDE.hi);
  case 0x1E:
    return CPU_8BIT_LOAD(m_RegisterDE.lo);
  case 0x26:
    return CPU_8BIT_LOAD(m_RegisterHL.hi);
  case 0x2E:
    return CPU_8BIT_LOAD(m_RegisterHL.lo);

  // load reg
  case 0x7F:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterAF.hi, 4);
  case 0x78:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterBC.hi, 4);
  case 0x79:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterBC.lo, 4);
  case 0x7A:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterDE.hi, 4);
  case 0x7B:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterDE.lo, 4);
  case 0x7C:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterHL.hi, 4);
  case 0x7D:
    return CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterHL.lo, 4);
  case 0x40:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterBC.hi, 4);
  case 0x41:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterBC.lo, 4);
  case 0x42:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterDE.hi, 4);
  case 0x43:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterDE.lo, 4);
  case 0x44:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterHL.hi, 4);
  case 0x45:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterHL.lo, 4);
  case 0x48:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterBC.hi, 4);
  case 0x49:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterBC.lo, 4);
  case 0x4A:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterDE.hi, 4);
  case 0x4B:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterDE.lo, 4);
  case 0x4C:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterHL.hi, 4);
  case 0x4D:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterHL.lo, 4);
  case 0x50:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterBC.hi, 4);
  case 0x51:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterBC.lo, 4);
  case 0x52:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterDE.hi, 4);
  case 0x53:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterDE.lo, 4);
  case 0x54:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterHL.hi, 4);
  case 0x55:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterHL.lo, 4);
  case 0x58:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterBC.hi, 4);
  case 0x59:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterBC.lo, 4);
  case 0x5A:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterDE.hi, 4);
  case 0x5B:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterDE.lo, 4);
  case 0x5C:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterHL.hi, 4);
  case 0x5D:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterHL.lo, 4);
  case 0x60:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterBC.hi, 4);
  case 0x61:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterBC.lo, 4);
  case 0x62:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterDE.hi, 4);
  case 0x63:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterDE.lo, 4);
  case 0x64:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterHL.hi, 4);
  case 0x65:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterHL.lo, 4);
  case 0x68:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterBC.hi, 4);
  case 0x69:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterBC.lo, 4);
  case 0x6A:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterDE.hi, 4);
  case 0x6B:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterDE.lo, 4);
  case 0x6C:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterHL.hi, 4);
  case 0x6D:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterHL.lo, 4);

  // write reg to memory
  case 0x70:
    WriteMemory(m_RegisterHL.reg, m_RegisterBC.hi);
    return 8;
  case 0x71:
    WriteMemory(m_RegisterHL.reg, m_RegisterBC.lo);
    return 8;
  case 0x72:
    WriteMemory(m_RegisterHL.reg, m_RegisterDE.hi);
    return 8;
  case 0x73:
    WriteMemory(m_RegisterHL.reg, m_RegisterDE.lo);
    return 8;
  case 0x74:
    WriteMemory(m_RegisterHL.reg, m_RegisterHL.hi);
    return 8;
  case 0x75:
    WriteMemory(m_RegisterHL.reg, m_RegisterHL.lo);
    return 8;

  // write memory to reg
  case 0x7E:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterHL.reg);
  case 0x46:
    return CPU_REG_LOAD_ROM(m_RegisterBC.hi, m_RegisterHL.reg);
  case 0x4E:
    return CPU_REG_LOAD_ROM(m_RegisterBC.lo, m_RegisterHL.reg);
  case 0x56:
    return CPU_REG_LOAD_ROM(m_RegisterDE.hi, m_RegisterHL.reg);
  case 0x5E:
    return CPU_REG_LOAD_ROM(m_RegisterDE.lo, m_RegisterHL.reg);
  case 0x66:
    return CPU_REG_LOAD_ROM(m_RegisterHL.hi, m_RegisterHL.reg);
  case 0x6E:
    return CPU_REG_LOAD_ROM(m_RegisterHL.lo, m_RegisterHL.reg);
  case 0x0A:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterBC.reg);
  case 0x1A:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterDE.reg);
  case 0xF2:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, (0xFF00 + m_RegisterBC.lo));

  // put a into register
  case 0x47:
    return CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterAF.hi, 4);
  case 0x4F:
    return CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterAF.hi, 4);
  case 0x57:
    return CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterAF.hi, 4);
  case 0x5F:
    return CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterAF.hi, 4);
  case 0x67:
    return CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterAF.hi, 4);
  case 0x6F:
    return CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterAF.hi, 4);

  // put a into memory address
  case 0x02:
    WriteMemory(m_RegisterBC.reg, m_RegisterAF.hi);
    return 8;
  case 0x12:
    WriteMemory(m_RegisterDE.reg, m_RegisterAF.hi);
    return 8;
  case 0x77:
    WriteMemory(m_RegisterHL.reg, m_RegisterAF.hi);
    return 8;
  case 0xE2:
    WriteMemory((0xFF00 + m_RegisterBC.lo), m_RegisterAF.hi);
    return 8;

  // put memory into a, decrement/increment memory
  case 0x3A:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterHL.reg);
    CPU_16BIT_DEC(m_RegisterHL.reg, 0);
  case 0x2A:
    return CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterHL.reg);
    CPU_16BIT_INC(m_RegisterHL.reg, 0);

  // put a into memory, decrement/increment reg
  case 0x32:
    WriteMemory(m_RegisterHL.reg, m_RegisterAF.hi);
    CPU_16BIT_DEC(m_RegisterHL.reg, 0);
    return 8;
  case 0x22:
    WriteMemory(m_RegisterHL.reg, m_RegisterAF.hi);
    CPU_16BIT_INC(m_RegisterHL.reg, 0);
    return 8;

  // 16 bit loads
  case 0x01:
    return CPU_16BIT_LOAD(m_RegisterBC.reg);
  case 0x11:
    return CPU_16BIT_LOAD(m_RegisterDE.reg);
  case 0x21:
    return CPU_16BIT_LOAD(m_RegisterHL.reg);
  case 0x31:
    return CPU_16BIT_LOAD(m_StackPointer.reg);
  case 0xF9:
    m_StackPointer.reg = m_RegisterHL.reg;
    return 8;

  // push word onto stack
  case 0xF5:
    PushWordOntoStack(m_RegisterAF.reg);
    return 16;
  case 0xC5:
    PushWordOntoStack(m_RegisterBC.reg);
    return 16;
  case 0xD5:
    PushWordOntoStack(m_RegisterDE.reg);
    return 16;
  case 0xE5:
    PushWordOntoStack(m_RegisterHL.reg);
    return 16;

  // pop word from stack into reg
  case 0xF1:
    m_RegisterAF.reg = PopWordOffStack();
    return 12;
  case 0xC1:
    m_RegisterBC.reg = PopWordOffStack();
    return 12;
  case 0xD1:
    m_RegisterDE.reg = PopWordOffStack();
    return 12;
  case 0xE1:
    m_RegisterHL.reg = PopWordOffStack();
    return 12;

  // 8-bit add
  case 0x87:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterAF.hi, 4, false, false);
  case 0x80:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.hi, 4, false, false);
  case 0x81:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.lo, 4, false, false);
  case 0x82:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.hi, 4, false, false);
  case 0x83:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.lo, 4, false, false);
  case 0x84:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.hi, 4, false, false);
  case 0x85:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.lo, 4, false, false);
  case 0x86:
    return CPU_8BIT_ADD(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8, false,
                        false);
  case 0xC6:
    return CPU_8BIT_ADD(m_RegisterAF.hi, 0, 8, true, false);

  // 8-bit add + carry
  case 0x8F:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterAF.hi, 4, false, true);
  case 0x88:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.hi, 4, false, true);
  case 0x89:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.lo, 4, false, true);
  case 0x8A:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.hi, 4, false, true);
  case 0x8B:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.lo, 4, false, true);
  case 0x8C:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.hi, 4, false, true);
  case 0x8D:
    return CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.lo, 4, false, true);
  case 0x8E:
    return CPU_8BIT_ADD(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8, false,
                        true);
  case 0xCE:
    return CPU_8BIT_ADD(m_RegisterAF.hi, 0, 8, true, true);

  // 8-bit subtract
  case 0x97:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterAF.hi, 4, false, false);
  case 0x90:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.hi, 4, false, false);
  case 0x91:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.lo, 4, false, false);
  case 0x92:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.hi, 4, false, false);
  case 0x93:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.lo, 4, false, false);
  case 0x94:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.hi, 4, false, false);
  case 0x95:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.lo, 4, false, false);
  case 0x96:
    return CPU_8BIT_SUB(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8, false,
                        false);
  case 0xD6:
    return CPU_8BIT_SUB(m_RegisterAF.hi, 0, 8, true, false);

  // 8-bit subtract + carry
  case 0x9F:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterAF.hi, 4, false, true);
  case 0x98:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.hi, 4, false, true);
  case 0x99:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.lo, 4, false, true);
  case 0x9A:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.hi, 4, false, true);
  case 0x9B:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.lo, 4, false, true);
  case 0x9C:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.hi, 4, false, true);
  case 0x9D:
    return CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.lo, 4, false, true);
  case 0x9E:
    return CPU_8BIT_SUB(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8, false,
                        true);
  case 0xDE:
    return CPU_8BIT_SUB(m_RegisterAF.hi, 0, 8, true, true);

  // 8-bit AND reg with reg
  case 0xA7:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterAF.hi, 4, false);
  case 0xA0:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterBC.hi, 4, false);
  case 0xA1:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterBC.lo, 4, false);
  case 0xA2:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterDE.hi, 4, false);
  case 0xA3:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterDE.lo, 4, false);
  case 0xA4:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterHL.hi, 4, false);
  case 0xA5:
    return CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterHL.lo, 4, false);
  case 0xA6:
    return CPU_8BIT_AND(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8,
                        false);
  case 0xE6:
    return CPU_8BIT_AND(m_RegisterAF.hi, 0, 8, true);

  // 8-bit OR reg with reg
  case 0xB7:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterAF.hi, 4, false);
  case 0xB0:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterBC.hi, 4, false);
  case 0xB1:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterBC.lo, 4, false);
  case 0xB2:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterDE.hi, 4, false);
  case 0xB3:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterDE.lo, 4, false);
  case 0xB4:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterHL.hi, 4, false);
  case 0xB5:
    return CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterHL.lo, 4, false);
  case 0xB6:
    return CPU_8BIT_OR(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8, false);
  case 0xF6:
    return CPU_8BIT_OR(m_RegisterAF.hi, 0, 8, true);

  // 8-bit XOR reg with reg
  case 0xAF:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterAF.hi, 4, false);
  case 0xA8:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterBC.hi, 4, false);
  case 0xA9:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterBC.lo, 4, false);
  case 0xAA:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterDE.hi, 4, false);
  case 0xAB:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterDE.lo, 4, false);
  case 0xAC:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterHL.hi, 4, false);
  case 0xAD:
    return CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterHL.lo, 4, false);
  case 0xAE:
    return CPU_8BIT_XOR(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8,
                        false);
  case 0xEE:
    return CPU_8BIT_XOR(m_RegisterAF.hi, 0, 8, true);

  // 8-Bit compare
  case 0xBF:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterAF.hi, 4, false);
  case 0xB8:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterBC.hi, 4, false);
  case 0xB9:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterBC.lo, 4, false);
  case 0xBA:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterDE.hi, 4, false);
  case 0xBB:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterDE.lo, 4, false);
  case 0xBC:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterHL.hi, 4, false);
  case 0xBD:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterHL.lo, 4, false);
  case 0xBE:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg), 8,
                            false);
  case 0xFE:
    return CPU_8BIT_COMPARE(m_RegisterAF.hi, 0, 8, true);

  // 8-bit inc
  case 0x3C:
    return CPU_8BIT_INC(m_RegisterAF.hi, 4);
  case 0x04:
    return CPU_8BIT_INC(m_RegisterBC.hi, 4);
  case 0x0C:
    return CPU_8BIT_INC(m_RegisterBC.lo, 4);
  case 0x14:
    return CPU_8BIT_INC(m_RegisterDE.hi, 4);
  case 0x1C:
    return CPU_8BIT_INC(m_RegisterDE.lo, 4);
  case 0x24:
    return CPU_8BIT_INC(m_RegisterHL.hi, 4);
  case 0x2C:
    return CPU_8BIT_INC(m_RegisterHL.lo, 4);
  case 0x34:
    return CPU_8BIT_MEMORY_INC(m_RegisterHL.reg, 12);

  // 8-bit dec
  case 0x3D:
    return CPU_8BIT_DEC(m_RegisterAF.hi, 4);
  case 0x05:
    return CPU_8BIT_DEC(m_RegisterBC.hi, 4);
  case 0x0D:
    return CPU_8BIT_DEC(m_RegisterBC.lo, 4);
  case 0x15:
    return CPU_8BIT_DEC(m_RegisterDE.hi, 4);
  case 0x1D:
    return CPU_8BIT_DEC(m_RegisterDE.lo, 4);
  case 0x25:
    return CPU_8BIT_DEC(m_RegisterHL.hi, 4);
  case 0x2D:
    return CPU_8BIT_DEC(m_RegisterHL.lo, 4);
  case 0x35:
    return CPU_8BIT_MEMORY_DEC(m_RegisterHL.reg, 12);

    // 16-bit add
  case 0x09:
    return CPU_16BIT_ADD(m_RegisterHL.reg, m_RegisterBC.reg, 8);
  case 0x19:
    return CPU_16BIT_ADD(m_RegisterHL.reg, m_RegisterDE.reg, 8);
  case 0x29:
    return CPU_16BIT_ADD(m_RegisterHL.reg, m_RegisterHL.reg, 8);
  case 0x39:
    return CPU_16BIT_ADD(m_RegisterHL.reg, m_StackPointer.reg, 8);

    // inc 16-bit register
  case 0x03:
    return CPU_16BIT_INC(m_RegisterBC.reg, 8);
  case 0x13:
    return CPU_16BIT_INC(m_RegisterDE.reg, 8);
  case 0x23:
    return CPU_16BIT_INC(m_RegisterHL.reg, 8);
  case 0x33:
    return CPU_16BIT_INC(m_StackPointer.reg, 8);

  // dec 16-bit register
  case 0x0B:
    return CPU_16BIT_DEC(m_RegisterBC.reg, 8);
  case 0x1B:
    return CPU_16BIT_DEC(m_RegisterDE.reg, 8);
  case 0x2B:
    return CPU_16BIT_DEC(m_RegisterHL.reg, 8);
  case 0x3B:
    return CPU_16BIT_DEC(m_StackPointer.reg, 8);

  // jumps
  case 0xE9:
    m_ProgramCounter = m_RegisterHL.reg;
    return 4;
  case 0xC3:
    return CPU_JUMP(false, 0, false);
  case 0xC2:
    return CPU_JUMP(true, FLAG_Z, false);
  case 0xCA:
    return CPU_JUMP(true, FLAG_Z, true);
  case 0xD2:
    return CPU_JUMP(true, FLAG_C, false);
  case 0xDA:
    return CPU_JUMP(true, FLAG_C, true);

  // jump with immediate data
  case 0x18:
    return CPU_JUMP_IMMEDIATE(false, 0, false);
  case 0x20:
    return CPU_JUMP_IMMEDIATE(true, FLAG_Z, false);
  case 0x28:
    return CPU_JUMP_IMMEDIATE(true, FLAG_Z, true);
  case 0x30:
    return CPU_JUMP_IMMEDIATE(true, FLAG_C, false);
  case 0x38:
    return CPU_JUMP_IMMEDIATE(true, FLAG_C, true);

  // calls
  case 0xCD:
    return CPU_CALL(false, 0, false);
  case 0xC4:
    return CPU_CALL(true, FLAG_Z, false);
  case 0xCC:
    return CPU_CALL(true, FLAG_Z, true);
  case 0xD4:
    return CPU_CALL(true, FLAG_C, false);
  case 0xDC:
    return CPU_CALL(true, FLAG_C, true);

    // returns
  case 0xC9:
    return CPU_RETURN(false, 0, false);
  case 0xC0:
    return CPU_RETURN(true, FLAG_Z, false);
  case 0xC8:
    return CPU_RETURN(true, FLAG_Z, true);
  case 0xD0:
    return CPU_RETURN(true, FLAG_C, false);
  case 0xD8:
    return CPU_RETURN(true, FLAG_C, true);

  // restarts
  case 0xC7:
    return CPU_RESTARTS(0x00);
  case 0xCF:
    return CPU_RESTARTS(0x08);
  case 0xD7:
    return CPU_RESTARTS(0x10);
  case 0xDF:
    return CPU_RESTARTS(0x18);
  case 0xE7:
    return CPU_RESTARTS(0x20);
  case 0xEF:
    return CPU_RESTARTS(0x28);
  case 0xF7:
    return CPU_RESTARTS(0x30);
  case 0xFF:
    return CPU_RESTARTS(0x38);

  case 0x27:
    return CPU_DAA();

  // handle the extended opcodes
  case 0xCB:
    return ExecuteExtendedOpcode();

  // unique instructions
  case 0x07:
    return CPU_RLC(m_RegisterAF.hi);
  case 0x0F:
    return CPU_RRC(m_RegisterAF.hi);
  case 0x17:
    return CPU_RL(m_RegisterAF.hi);
  case 0x1F:
    return CPU_RR(m_RegisterAF.hi);

  // return from interrupt
  case 0xD9: {
    m_ProgramCounter = PopWordOffStack();
    WriteMemory(INTERRUPT_ENABLED_REGISTER, true);
    return 8;
  }

  case 0x08: {
    WORD nn = ReadWord();
    m_ProgramCounter += 2;
    WriteMemory(nn, m_StackPointer.lo);
    nn++;
    WriteMemory(nn, m_StackPointer.hi);
    return 20;
  }

  case 0x36: {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    WriteMemory(m_RegisterHL.reg, n);
    return 12;
  }

  case 0xFA: {
    WORD nn = ReadWord();
    m_ProgramCounter += 2;
    BYTE n = ReadMemory(nn);
    m_RegisterAF.hi = n;
    return 16;
  }

  case 0x3E: {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    m_RegisterAF.hi = n;
    return 8;
  }

  case 0xEA: {
    WORD nn = ReadWord();
    m_ProgramCounter += 2;
    WriteMemory(nn, m_RegisterAF.hi);
    return 16;
  }

  case 0xF3: {
      WriteMemory(INTERRUPT_ENABLED_REGISTER, false);
    return 4;
  }

  case 0xFB: {
  WriteMemory(INTERRUPT_ENABLED_REGISTER, true);
    return 4;
  }

  case 0xE0: {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    WORD address = 0xFF00 + n;
    WriteMemory(address, m_RegisterAF.hi);
    return 12;
  }

  case 0xF0: {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    WORD address = 0xFF00 + n;
    m_RegisterAF.hi = ReadMemory(address);
    return 12;
  }

  case 0x2F: {
    m_RegisterAF.hi ^= 0xFF;

    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N);
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
    return 4;
  }

  // halt
  case 0x76: {
    exit(0);
    return 4;
  }

  case 0x3F: {
    if (TestBit(m_RegisterAF.lo, FLAG_C))
      m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_C);
    else
      m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);
    return 4;
  }

  case 0x37: {
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);
    return 4;
  }

  case 0xF8: {
    SIGNED_BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);

    WORD value = (m_StackPointer.reg + n) & 0xFFFF;

    m_RegisterHL.reg = value;
    unsigned int v = m_StackPointer.reg + n;

    if (n > 0xFFFF)
      m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    else
      m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_C);

    if ((m_StackPointer.reg & 0xF) + (n & 0xF) > 0xF)
      m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
    else
      m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);
  }

  case 0x10: {
    m_ProgramCounter++;
    return 4;
  }

  default:
    assert(false);
  }
}

int Emulator::ExecuteExtendedOpcode() {
  BYTE opcode = m_Rom[m_ProgramCounter];

  if ((m_ProgramCounter >= 0x4000 && m_ProgramCounter <= 0x7FFF) ||
      (m_ProgramCounter >= 0xA000 && m_ProgramCounter <= 0xBFFF))
    opcode = ReadMemory(m_ProgramCounter);

  m_ProgramCounter++;

  switch (opcode) {
  // rotate left through carry
  case 0x0:
    return CPU_RLC(m_RegisterBC.hi);
  case 0x1:
    return CPU_RLC(m_RegisterBC.lo);
  case 0x2:
    return CPU_RLC(m_RegisterDE.hi);
  case 0x3:
    return CPU_RLC(m_RegisterDE.lo);
  case 0x4:
    return CPU_RLC(m_RegisterHL.hi);
  case 0x5:
    return CPU_RLC(m_RegisterHL.lo);
  case 0x6:
    return CPU_RLC_MEMORY(m_RegisterHL.reg);
  case 0x7:
    return CPU_RLC(m_RegisterAF.hi);

  // rotate right through carry
  case 0x8:
    return CPU_RRC(m_RegisterBC.hi);
  case 0x9:
    return CPU_RRC(m_RegisterBC.lo);
  case 0xA:
    return CPU_RRC(m_RegisterDE.hi);
  case 0xB:
    return CPU_RRC(m_RegisterDE.lo);
  case 0xC:
    return CPU_RRC(m_RegisterHL.hi);
  case 0xD:
    return CPU_RRC(m_RegisterHL.lo);
  case 0xE:
    return CPU_RRC_MEMORY(m_RegisterHL.reg);
  case 0xF:
    return CPU_RRC(m_RegisterAF.hi);

  // rotate left
  case 0x10:
    return CPU_RL(m_RegisterBC.hi);
    break;
  case 0x11:
    return CPU_RL(m_RegisterBC.lo);
    break;
  case 0x12:
    return CPU_RL(m_RegisterDE.hi);
    break;
  case 0x13:
    return CPU_RL(m_RegisterDE.lo);
    break;
  case 0x14:
    return CPU_RL(m_RegisterHL.hi);
    break;
  case 0x15:
    return CPU_RL(m_RegisterHL.lo);
    break;
  case 0x16:
    return CPU_RL_MEMORY(m_RegisterHL.reg);
    break;
  case 0x17:
    return CPU_RL(m_RegisterAF.hi);
    break;

  // rotate right
  case 0x18:
    return CPU_RR(m_RegisterBC.hi);
    break;
  case 0x19:
    return CPU_RR(m_RegisterBC.lo);
    break;
  case 0x1A:
    return CPU_RR(m_RegisterDE.hi);
    break;
  case 0x1B:
    return CPU_RR(m_RegisterDE.lo);
    break;
  case 0x1C:
    return CPU_RR(m_RegisterHL.hi);
    break;
  case 0x1D:
    return CPU_RR(m_RegisterHL.lo);
    break;
  case 0x1E:
    return CPU_RR_MEMORY(m_RegisterHL.reg);
    break;
  case 0x1F:
    return CPU_RR(m_RegisterAF.hi);
    break;

  case 0x20:
    return CPU_SLA(m_RegisterBC.hi);
  case 0x21:
    return CPU_SLA(m_RegisterBC.lo);
  case 0x22:
    return CPU_SLA(m_RegisterDE.hi);
  case 0x23:
    return CPU_SLA(m_RegisterDE.lo);
  case 0x24:
    return CPU_SLA(m_RegisterHL.hi);
  case 0x25:
    return CPU_SLA(m_RegisterHL.lo);
  case 0x26:
    return CPU_SLA_MEMORY(m_RegisterHL.reg);
  case 0x27:
    return CPU_SLA(m_RegisterAF.hi);

  case 0x28:
    return CPU_SRA(m_RegisterBC.hi);
  case 0x29:
    return CPU_SRA(m_RegisterBC.lo);
  case 0x2A:
    return CPU_SRA(m_RegisterDE.hi);
  case 0x2B:
    return CPU_SRA(m_RegisterDE.lo);
  case 0x2C:
    return CPU_SRA(m_RegisterHL.hi);
  case 0x2D:
    return CPU_SRA(m_RegisterHL.lo);
  case 0x2E:
    return CPU_SRA_MEMORY(m_RegisterHL.reg);
  case 0x2F:
    return CPU_SRA(m_RegisterAF.hi);

  case 0x38:
    return CPU_SRL(m_RegisterBC.hi);
  case 0x39:
    return CPU_SRL(m_RegisterBC.lo);
  case 0x3A:
    return CPU_SRL(m_RegisterDE.hi);
  case 0x3B:
    return CPU_SRL(m_RegisterDE.lo);
  case 0x3C:
    return CPU_SRL(m_RegisterHL.hi);
  case 0x3D:
    return CPU_SRL(m_RegisterHL.lo);
  case 0x3E:
    return CPU_SRL_MEMORY(m_RegisterHL.reg);
  case 0x3F:
    return CPU_SRL(m_RegisterAF.hi);

  // swap nibbles
  case 0x37:
    return CPU_SWAP_NIBBLES(m_RegisterAF.hi);
  case 0x30:
    return CPU_SWAP_NIBBLES(m_RegisterBC.hi);
  case 0x31:
    return CPU_SWAP_NIBBLES(m_RegisterBC.lo);
  case 0x32:
    return CPU_SWAP_NIBBLES(m_RegisterDE.hi);
  case 0x33:
    return CPU_SWAP_NIBBLES(m_RegisterDE.lo);
  case 0x34:
    return CPU_SWAP_NIBBLES(m_RegisterHL.hi);
  case 0x35:
    return CPU_SWAP_NIBBLES(m_RegisterHL.lo);
  case 0x36:
    return CPU_SWAP_NIB_MEM(m_RegisterHL.reg);

  // test bit
  case 0x40:
    return CPU_TEST_BIT(m_RegisterBC.hi, 0, 8);
  case 0x41:
    return CPU_TEST_BIT(m_RegisterBC.lo, 0, 8);
  case 0x42:
    return CPU_TEST_BIT(m_RegisterDE.hi, 0, 8);
  case 0x43:
    return CPU_TEST_BIT(m_RegisterDE.lo, 0, 8);
  case 0x44:
    return CPU_TEST_BIT(m_RegisterHL.hi, 0, 8);
  case 0x45:
    return CPU_TEST_BIT(m_RegisterHL.lo, 0, 8);
  case 0x46:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 0, 16);
  case 0x47:
    return CPU_TEST_BIT(m_RegisterAF.hi, 0, 8);
  case 0x48:
    return CPU_TEST_BIT(m_RegisterBC.hi, 1, 8);
  case 0x49:
    return CPU_TEST_BIT(m_RegisterBC.lo, 1, 8);
  case 0x4A:
    return CPU_TEST_BIT(m_RegisterDE.hi, 1, 8);
  case 0x4B:
    return CPU_TEST_BIT(m_RegisterDE.lo, 1, 8);
  case 0x4C:
    return CPU_TEST_BIT(m_RegisterHL.hi, 1, 8);
  case 0x4D:
    return CPU_TEST_BIT(m_RegisterHL.lo, 1, 8);
  case 0x4E:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 1, 16);
  case 0x4F:
    return CPU_TEST_BIT(m_RegisterAF.hi, 1, 8);
  case 0x50:
    return CPU_TEST_BIT(m_RegisterBC.hi, 2, 8);
  case 0x51:
    return CPU_TEST_BIT(m_RegisterBC.lo, 2, 8);
  case 0x52:
    return CPU_TEST_BIT(m_RegisterDE.hi, 2, 8);
  case 0x53:
    return CPU_TEST_BIT(m_RegisterDE.lo, 2, 8);
  case 0x54:
    return CPU_TEST_BIT(m_RegisterHL.hi, 2, 8);
  case 0x55:
    return CPU_TEST_BIT(m_RegisterHL.lo, 2, 8);
  case 0x56:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 2, 16);
  case 0x57:
    return CPU_TEST_BIT(m_RegisterAF.hi, 2, 8);
  case 0x58:
    return CPU_TEST_BIT(m_RegisterBC.hi, 3, 8);
  case 0x59:
    return CPU_TEST_BIT(m_RegisterBC.lo, 3, 8);
  case 0x5A:
    return CPU_TEST_BIT(m_RegisterDE.hi, 3, 8);
  case 0x5B:
    return CPU_TEST_BIT(m_RegisterDE.lo, 3, 8);
  case 0x5C:
    return CPU_TEST_BIT(m_RegisterHL.hi, 3, 8);
  case 0x5D:
    return CPU_TEST_BIT(m_RegisterHL.lo, 3, 8);
  case 0x5E:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 3, 16);
  case 0x5F:
    return CPU_TEST_BIT(m_RegisterAF.hi, 3, 8);
  case 0x60:
    return CPU_TEST_BIT(m_RegisterBC.hi, 4, 8);
  case 0x61:
    return CPU_TEST_BIT(m_RegisterBC.lo, 4, 8);
  case 0x62:
    return CPU_TEST_BIT(m_RegisterDE.hi, 4, 8);
  case 0x63:
    return CPU_TEST_BIT(m_RegisterDE.lo, 4, 8);
  case 0x64:
    return CPU_TEST_BIT(m_RegisterHL.hi, 4, 8);
  case 0x65:
    return CPU_TEST_BIT(m_RegisterHL.lo, 4, 8);
  case 0x66:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 4, 16);
  case 0x67:
    return CPU_TEST_BIT(m_RegisterAF.hi, 4, 8);
  case 0x68:
    return CPU_TEST_BIT(m_RegisterBC.hi, 5, 8);
  case 0x69:
    return CPU_TEST_BIT(m_RegisterBC.lo, 5, 8);
  case 0x6A:
    return CPU_TEST_BIT(m_RegisterDE.hi, 5, 8);
  case 0x6B:
    return CPU_TEST_BIT(m_RegisterDE.lo, 5, 8);
  case 0x6C:
    return CPU_TEST_BIT(m_RegisterHL.hi, 5, 8);
  case 0x6D:
    return CPU_TEST_BIT(m_RegisterHL.lo, 5, 8);
  case 0x6E:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 5, 16);
  case 0x6F:
    return CPU_TEST_BIT(m_RegisterAF.hi, 5, 8);
  case 0x70:
    return CPU_TEST_BIT(m_RegisterBC.hi, 6, 8);
  case 0x71:
    return CPU_TEST_BIT(m_RegisterBC.lo, 6, 8);
  case 0x72:
    return CPU_TEST_BIT(m_RegisterDE.hi, 6, 8);
  case 0x73:
    return CPU_TEST_BIT(m_RegisterDE.lo, 6, 8);
  case 0x74:
    return CPU_TEST_BIT(m_RegisterHL.hi, 6, 8);
  case 0x75:
    return CPU_TEST_BIT(m_RegisterHL.lo, 6, 8);
  case 0x76:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 6, 16);
  case 0x77:
    return CPU_TEST_BIT(m_RegisterAF.hi, 6, 8);
  case 0x78:
    return CPU_TEST_BIT(m_RegisterBC.hi, 7, 8);
  case 0x79:
    return CPU_TEST_BIT(m_RegisterBC.lo, 7, 8);
  case 0x7A:
    return CPU_TEST_BIT(m_RegisterDE.hi, 7, 8);
  case 0x7B:
    return CPU_TEST_BIT(m_RegisterDE.lo, 7, 8);
  case 0x7C:
    return CPU_TEST_BIT(m_RegisterHL.hi, 7, 8);
  case 0x7D:
    return CPU_TEST_BIT(m_RegisterHL.lo, 7, 8);
  case 0x7E:
    return CPU_TEST_BIT(ReadMemory(m_RegisterHL.reg), 7, 16);
  case 0x7F:
    return CPU_TEST_BIT(m_RegisterAF.hi, 7, 8);

  // reset bit
  case 0x80:
    return CPU_RESET_BIT(m_RegisterBC.hi, 0);
  case 0x81:
    return CPU_RESET_BIT(m_RegisterBC.lo, 0);
  case 0x82:
    return CPU_RESET_BIT(m_RegisterDE.hi, 0);
  case 0x83:
    return CPU_RESET_BIT(m_RegisterDE.lo, 0);
  case 0x84:
    return CPU_RESET_BIT(m_RegisterHL.hi, 0);
  case 0x85:
    return CPU_RESET_BIT(m_RegisterHL.lo, 0);
  case 0x86:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 0);
  case 0x87:
    return CPU_RESET_BIT(m_RegisterAF.hi, 0);
  case 0x88:
    return CPU_RESET_BIT(m_RegisterBC.hi, 1);
  case 0x89:
    return CPU_RESET_BIT(m_RegisterBC.lo, 1);
  case 0x8A:
    return CPU_RESET_BIT(m_RegisterDE.hi, 1);
  case 0x8B:
    return CPU_RESET_BIT(m_RegisterDE.lo, 1);
  case 0x8C:
    return CPU_RESET_BIT(m_RegisterHL.hi, 1);
  case 0x8D:
    return CPU_RESET_BIT(m_RegisterHL.lo, 1);
  case 0x8E:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 1);
  case 0x8F:
    return CPU_RESET_BIT(m_RegisterAF.hi, 1);
  case 0x90:
    return CPU_RESET_BIT(m_RegisterBC.hi, 2);
  case 0x91:
    return CPU_RESET_BIT(m_RegisterBC.lo, 2);
  case 0x92:
    return CPU_RESET_BIT(m_RegisterDE.hi, 2);
  case 0x93:
    return CPU_RESET_BIT(m_RegisterDE.lo, 2);
  case 0x94:
    return CPU_RESET_BIT(m_RegisterHL.hi, 2);
  case 0x95:
    return CPU_RESET_BIT(m_RegisterHL.lo, 2);
  case 0x96:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 2);
  case 0x97:
    return CPU_RESET_BIT(m_RegisterAF.hi, 2);
  case 0x98:
    return CPU_RESET_BIT(m_RegisterBC.hi, 3);
  case 0x99:
    return CPU_RESET_BIT(m_RegisterBC.lo, 3);
  case 0x9A:
    return CPU_RESET_BIT(m_RegisterDE.hi, 3);
  case 0x9B:
    return CPU_RESET_BIT(m_RegisterDE.lo, 3);
  case 0x9C:
    return CPU_RESET_BIT(m_RegisterHL.hi, 3);
  case 0x9D:
    return CPU_RESET_BIT(m_RegisterHL.lo, 3);
  case 0x9E:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 3);
  case 0x9F:
    return CPU_RESET_BIT(m_RegisterAF.hi, 3);
  case 0xA0:
    return CPU_RESET_BIT(m_RegisterBC.hi, 4);
  case 0xA1:
    return CPU_RESET_BIT(m_RegisterBC.lo, 4);
  case 0xA2:
    return CPU_RESET_BIT(m_RegisterDE.hi, 4);
  case 0xA3:
    return CPU_RESET_BIT(m_RegisterDE.lo, 4);
  case 0xA4:
    return CPU_RESET_BIT(m_RegisterHL.hi, 4);
  case 0xA5:
    return CPU_RESET_BIT(m_RegisterHL.lo, 4);
  case 0xA6:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 4);
  case 0xA7:
    return CPU_RESET_BIT(m_RegisterAF.hi, 4);
  case 0xA8:
    return CPU_RESET_BIT(m_RegisterBC.hi, 5);
  case 0xA9:
    return CPU_RESET_BIT(m_RegisterBC.lo, 5);
  case 0xAA:
    return CPU_RESET_BIT(m_RegisterDE.hi, 5);
  case 0xAB:
    return CPU_RESET_BIT(m_RegisterDE.lo, 5);
  case 0xAC:
    return CPU_RESET_BIT(m_RegisterHL.hi, 5);
  case 0xAD:
    return CPU_RESET_BIT(m_RegisterHL.lo, 5);
  case 0xAE:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 5);
  case 0xAF:
    return CPU_RESET_BIT(m_RegisterAF.hi, 5);
  case 0xB0:
    return CPU_RESET_BIT(m_RegisterBC.hi, 6);
  case 0xB1:
    return CPU_RESET_BIT(m_RegisterBC.lo, 6);
  case 0xB2:
    return CPU_RESET_BIT(m_RegisterDE.hi, 6);
  case 0xB3:
    return CPU_RESET_BIT(m_RegisterDE.lo, 6);
  case 0xB4:
    return CPU_RESET_BIT(m_RegisterHL.hi, 6);
  case 0xB5:
    return CPU_RESET_BIT(m_RegisterHL.lo, 6);
  case 0xB6:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 6);
  case 0xB7:
    return CPU_RESET_BIT(m_RegisterAF.hi, 6);
  case 0xB8:
    return CPU_RESET_BIT(m_RegisterBC.hi, 7);
  case 0xB9:
    return CPU_RESET_BIT(m_RegisterBC.lo, 7);
  case 0xBA:
    return CPU_RESET_BIT(m_RegisterDE.hi, 7);
  case 0xBB:
    return CPU_RESET_BIT(m_RegisterDE.lo, 7);
  case 0xBC:
    return CPU_RESET_BIT(m_RegisterHL.hi, 7);
  case 0xBD:
    return CPU_RESET_BIT(m_RegisterHL.lo, 7);
  case 0xBE:
    return CPU_RESET_BIT_MEMORY(m_RegisterHL.reg, 7);
  case 0xBF:
    return CPU_RESET_BIT(m_RegisterAF.hi, 7);

  // set bit
  case 0xC0:
    return CPU_SET_BIT(m_RegisterBC.hi, 0);
  case 0xC1:
    return CPU_SET_BIT(m_RegisterBC.lo, 0);
  case 0xC2:
    return CPU_SET_BIT(m_RegisterDE.hi, 0);
  case 0xC3:
    return CPU_SET_BIT(m_RegisterDE.lo, 0);
  case 0xC4:
    return CPU_SET_BIT(m_RegisterHL.hi, 0);
  case 0xC5:
    return CPU_SET_BIT(m_RegisterHL.lo, 0);
  case 0xC6:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 0);
  case 0xC7:
    return CPU_SET_BIT(m_RegisterAF.hi, 0);
  case 0xC8:
    return CPU_SET_BIT(m_RegisterBC.hi, 1);
  case 0xC9:
    return CPU_SET_BIT(m_RegisterBC.lo, 1);
  case 0xCA:
    return CPU_SET_BIT(m_RegisterDE.hi, 1);
  case 0xCB:
    return CPU_SET_BIT(m_RegisterDE.lo, 1);
  case 0xCC:
    return CPU_SET_BIT(m_RegisterHL.hi, 1);
  case 0xCD:
    return CPU_SET_BIT(m_RegisterHL.lo, 1);
  case 0xCE:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 1);
  case 0xCF:
    return CPU_SET_BIT(m_RegisterAF.hi, 1);
  case 0xD0:
    return CPU_SET_BIT(m_RegisterBC.hi, 2);
  case 0xD1:
    return CPU_SET_BIT(m_RegisterBC.lo, 2);
  case 0xD2:
    return CPU_SET_BIT(m_RegisterDE.hi, 2);
  case 0xD3:
    return CPU_SET_BIT(m_RegisterDE.lo, 2);
  case 0xD4:
    return CPU_SET_BIT(m_RegisterHL.hi, 2);
  case 0xD5:
    return CPU_SET_BIT(m_RegisterHL.lo, 2);
  case 0xD6:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 2);
  case 0xD7:
    return CPU_SET_BIT(m_RegisterAF.hi, 2);
  case 0xD8:
    return CPU_SET_BIT(m_RegisterBC.hi, 3);
  case 0xD9:
    return CPU_SET_BIT(m_RegisterBC.lo, 3);
  case 0xDA:
    return CPU_SET_BIT(m_RegisterDE.hi, 3);
  case 0xDB:
    return CPU_SET_BIT(m_RegisterDE.lo, 3);
  case 0xDC:
    return CPU_SET_BIT(m_RegisterHL.hi, 3);
  case 0xDD:
    return CPU_SET_BIT(m_RegisterHL.lo, 3);
  case 0xDE:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 3);
  case 0xDF:
    return CPU_SET_BIT(m_RegisterAF.hi, 3);
  case 0xE0:
    return CPU_SET_BIT(m_RegisterBC.hi, 4);
  case 0xE1:
    return CPU_SET_BIT(m_RegisterBC.lo, 4);
  case 0xE2:
    return CPU_SET_BIT(m_RegisterDE.hi, 4);
  case 0xE3:
    return CPU_SET_BIT(m_RegisterDE.lo, 4);
  case 0xE4:
    return CPU_SET_BIT(m_RegisterHL.hi, 4);
  case 0xE5:
    return CPU_SET_BIT(m_RegisterHL.lo, 4);
  case 0xE6:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 4);
  case 0xE7:
    return CPU_SET_BIT(m_RegisterAF.hi, 4);
  case 0xE8:
    return CPU_SET_BIT(m_RegisterBC.hi, 5);
  case 0xE9:
    return CPU_SET_BIT(m_RegisterBC.lo, 5);
  case 0xEA:
    return CPU_SET_BIT(m_RegisterDE.hi, 5);
  case 0xEB:
    return CPU_SET_BIT(m_RegisterDE.lo, 5);
  case 0xEC:
    return CPU_SET_BIT(m_RegisterHL.hi, 5);
  case 0xED:
    return CPU_SET_BIT(m_RegisterHL.lo, 5);
  case 0xEE:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 5);
  case 0xEF:
    return CPU_SET_BIT(m_RegisterAF.hi, 5);
  case 0xF0:
    return CPU_SET_BIT(m_RegisterBC.hi, 6);
  case 0xF1:
    return CPU_SET_BIT(m_RegisterBC.lo, 6);
  case 0xF2:
    return CPU_SET_BIT(m_RegisterDE.hi, 6);
  case 0xF3:
    return CPU_SET_BIT(m_RegisterDE.lo, 6);
  case 0xF4:
    return CPU_SET_BIT(m_RegisterHL.hi, 6);
  case 0xF5:
    return CPU_SET_BIT(m_RegisterHL.lo, 6);
  case 0xF6:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 6);
  case 0xF7:
    return CPU_SET_BIT(m_RegisterAF.hi, 6);
  case 0xF8:
    return CPU_SET_BIT(m_RegisterBC.hi, 7);
  case 0xF9:
    return CPU_SET_BIT(m_RegisterBC.lo, 7);
  case 0xFA:
    return CPU_SET_BIT(m_RegisterDE.hi, 7);
  case 0xFB:
    return CPU_SET_BIT(m_RegisterDE.lo, 7);
  case 0xFC:
    return CPU_SET_BIT(m_RegisterHL.hi, 7);
  case 0xFD:
    return CPU_SET_BIT(m_RegisterHL.lo, 7);
  case 0xFE:
    return CPU_SET_BIT_MEMORY(m_RegisterHL.reg, 7);
  case 0xFF:
    return CPU_SET_BIT(m_RegisterAF.hi, 7);

  default:
    assert(false);
  }
}