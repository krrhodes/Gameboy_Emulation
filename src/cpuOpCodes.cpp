#include "cpuOpCodes.h"

// put 1 byte immediate data into reg
int Emulator::CPU_8BIT_LOAD(BYTE &reg) {
  BYTE n = ReadMemory(m_ProgramCounter);
  m_ProgramCounter++;
  reg = n;
  return 8;
}

// put 2 byte immediate data into reg
int Emulator::CPU_16BIT_LOAD(WORD &reg) {
  WORD n = ReadWord();
  m_ProgramCounter += 2;
  reg = n;
  return 12;
}

int Emulator::CPU_REG_LOAD(BYTE &reg, BYTE load, int cycles) {
  reg = load;
  return cycles;
}

int Emulator::CPU_REG_LOAD_ROM(BYTE &reg, WORD address) {
  reg = ReadMemory(address);
  return 8;
}

// apparently no flags affected
int Emulator::CPU_16BIT_DEC(WORD &word, int cycles) {
  word--;
  return cycles;
}

// apparently no flags affected
int Emulator::CPU_16BIT_INC(WORD &word, int cycles) {
  word++;
  return cycles;
}

// add to reg. Can be immediate data, and can also add the carry flag to the
// result
int Emulator::CPU_8BIT_ADD(BYTE &reg, BYTE toAdd, int cycles, bool useImmediate,
                           bool addCarry) {
  BYTE before = reg;
  BYTE adding = 0;

  // are we adding immediate data or the second param?
  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    adding = n;
  } else {
    adding = toAdd;
  }

  // are we also adding the carry flag?
  if (addCarry) {
    if (TestBit(m_RegisterAF.lo, FLAG_C))
      adding++;
  }

  reg += adding;

  // set the flags
  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WORD htest = (before & 0xF);
  htest += (adding & 0xF);

  if (htest > 0xF)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);

  if ((before + adding) > 0xFF)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  return cycles;
}

// subtracts away from reg, can also subtract the carry flag too
int Emulator::CPU_8BIT_SUB(BYTE &reg, BYTE subtracting, int cycles,
                           bool useImmediate, bool subCarry) {
  BYTE before = reg;
  BYTE toSubtract = 0;

  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    toSubtract = n;
  } else {
    toSubtract = subtracting;
  }

  if (subCarry) {
    if (TestBit(m_RegisterAF.lo, FLAG_C))
      toSubtract++;
  }

  reg -= toSubtract;

  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N);

  // set if no borrow
  if (before < toSubtract)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  SIGNED_WORD htest = (before & 0xF);
  htest -= (toSubtract & 0xF);

  if (htest < 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_AND(BYTE &reg, BYTE toAnd, int cycles,
                           bool useImmediate) {
  BYTE myand = 0;

  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    myand = n;
  } else {
    myand = toAnd;
  }

  reg &= myand;

  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_OR(BYTE &reg, BYTE toOr, int cycles, bool useImmediate) {
  BYTE myor = 0;

  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    myor = n;
  } else {
    myor = toOr;
  }

  reg |= myor;

  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return cycles;
}

int Emulator::CPU_8BIT_XOR(BYTE &reg, BYTE toXOr, int cycles,
                           bool useImmediate) {
  BYTE myxor = 0;

  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    myxor = n;
  } else {
    myxor = toXOr;
  }

  reg ^= myxor;

  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return cycles;
}

// this does not affect any registers, hence why im not passing a reference

int Emulator::CPU_8BIT_COMPARE(BYTE reg, BYTE subtracting, int cycles,
                               bool useImmediate) {
  BYTE before = reg;
  BYTE toSubtract = 0;

  if (useImmediate) {
    BYTE n = ReadMemory(m_ProgramCounter);
    m_ProgramCounter++;
    toSubtract = n;
  } else {
    toSubtract = subtracting;
  }

  reg -= toSubtract;

  m_RegisterAF.lo = 0;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N);

  // set if no borrow
  if (before < toSubtract)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  SIGNED_WORD htest = before & 0xF;
  htest -= (toSubtract & 0xF);

  if (htest < 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_INC(BYTE &reg, int cycles) {
  // WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO
  // CPU_8BIT_MEMORY_INC
  BYTE before = reg;

  reg++;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);

  if ((before & 0xF) == 0xF)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_MEMORY_INC(WORD address, int cycles) {
  // WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO
  // CPU_8BIT_INC

  BYTE before = ReadMemory(address);
  WriteMemory(address, (before + 1));
  BYTE now = before + 1;

  if (now == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);

  if ((before & 0xF) == 0xF)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_DEC(BYTE &reg, int cycles) {
  // WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO
  // CPU_8BIT_MEMORY_DEC
  BYTE before = reg;

  reg--;

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N);

  if ((before & 0x0F) == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_8BIT_MEMORY_DEC(WORD address, int cycles) {
  // WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO
  // CPU_8BIT_DEC

  BYTE before = ReadMemory(address);
  WriteMemory(address, (before - 1));
  BYTE now = before - 1;

  if (now == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N);

  if ((before & 0x0F) == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_16BIT_ADD(WORD &reg, WORD toAdd, int cycles) {
  WORD before = reg;

  reg += toAdd;

  m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);

  if ((before + toAdd) > 0xFFFF)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_C);

  if (((before & 0xFF00) & 0xF) + ((toAdd >> 8) & 0xF))
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);
  else
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_JUMP(bool useCondition, int flag, bool condition) {
  WORD nn = ReadWord();
  m_ProgramCounter += 2;

  if (!useCondition) {
    m_ProgramCounter = nn;
  } else if (TestBit(m_RegisterAF.lo, flag) == condition) {
    m_ProgramCounter = nn;
  }

  return 12;
}

int Emulator::CPU_JUMP_IMMEDIATE(bool useCondition, int flag, bool condition) {
  SIGNED_BYTE n = (SIGNED_BYTE)ReadMemory(m_ProgramCounter);

  if (!useCondition) {
    m_ProgramCounter += n;
  } else if (TestBit(m_RegisterAF.lo, flag) == condition) {
    m_ProgramCounter += n;
  }

  m_ProgramCounter++;

  return 8;
}

int Emulator::CPU_CALL(bool useCondition, int flag, bool condition) {
  WORD nn = ReadWord();
  m_ProgramCounter += 2;

  if (!useCondition) {
    PushWordOntoStack(m_ProgramCounter);
    m_ProgramCounter = nn;
  } else if (TestBit(m_RegisterAF.lo, flag) == condition) {
    PushWordOntoStack(m_ProgramCounter);
    m_ProgramCounter = nn;
  }

  return 12;
}

int Emulator::CPU_RETURN(bool useCondition, int flag, bool condition) {
  if (!useCondition) {
    m_ProgramCounter = PopWordOffStack();
  } else if (TestBit(m_RegisterAF.lo, flag) == condition) {
    m_ProgramCounter = PopWordOffStack();
  }

  return 8;
}

int Emulator::CPU_SWAP_NIBBLES(BYTE &reg) {
  m_RegisterAF.lo = 0;

  reg = (((reg & 0xF0) >> 4) | ((reg & 0x0F) << 4));

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SWAP_NIB_MEM
  return 8;
}

int Emulator::CPU_SWAP_NIB_MEM(WORD address) {
  m_RegisterAF.lo = 0;

  BYTE mem = ReadMemory(address);
  mem = (((mem & 0xF0) >> 4) | ((mem & 0x0F) << 4));

  WriteMemory(address, mem);

  if (mem == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SWAP_NIBBLES

  return 16;
}

int Emulator::CPU_RESTARTS(BYTE n) {
  PushWordOntoStack(m_ProgramCounter);
  m_ProgramCounter = n;

  return 32;
}

int Emulator::CPU_SHIFT_LEFT_CARRY(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SHIFT_LEFT_CARRY_MEMORY
  m_RegisterAF.lo = 0;
  if (TestBit(reg, 7))
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  reg = reg << 1;
  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

int Emulator::CPU_SHIFT_LEFT_CARRY_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SHIFT_LEFT_CARRY
  BYTE before = ReadMemory(address);

  m_RegisterAF.lo = 0;
  if (TestBit(before, 7))
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  before = before << 1;
  if (before == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, before);

  return 16;
}

int Emulator::CPU_RESET_BIT(BYTE &reg, int bit) {
  // WHEN EDITING THIS ALSO EDIT CPU_RESET_BIT_MEMORY
  reg = BitReset(reg, bit);

  return 8;
}

int Emulator::CPU_RESET_BIT_MEMORY(WORD address, int bit) {
  // WHEN EDITING THIS ALSO EDIT CPU_RESET_BIT
  BYTE mem = ReadMemory(address);
  mem = BitReset(mem, bit);
  WriteMemory(address, mem);

  return 16;
}

int Emulator::CPU_TEST_BIT(BYTE reg, int bit, int cycles) {
  if (TestBit(reg, bit))
    m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);
  else
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);
  m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H);

  return cycles;
}

int Emulator::CPU_SET_BIT(BYTE &reg, int bit) {
  // WHEN EDITING THIS ALSO EDIT CPU_SET_BIT_MEMORY
  reg = BitSet(reg, bit);

  return 8;
}

int Emulator::CPU_SET_BIT_MEMORY(WORD address, int bit) {
  // WHEN EDITING THIS ALSO EDIT CPU_SET_BIT
  BYTE mem = ReadMemory(address);
  mem = BitSet(mem, bit);
  WriteMemory(address, mem);

  return 16;
}

// STOLEN
int Emulator::CPU_DAA() {
  if (TestBit(m_RegisterAF.lo, FLAG_N)) {
    if ((m_RegisterAF.hi & 0x0F) > 0x09 || m_RegisterAF.lo & 0x20) {
      m_RegisterAF.hi -= 0x06; // Half borrow: (0-1) = (0xF-0x6) = 9
      if ((m_RegisterAF.hi & 0xF0) == 0xF0)
        m_RegisterAF.lo |= 0x10;
      else
        m_RegisterAF.lo &= ~0x10;
    }

    if ((m_RegisterAF.hi & 0xF0) > 0x90 || m_RegisterAF.lo & 0x10)
      m_RegisterAF.hi -= 0x60;
  } else {
    if ((m_RegisterAF.hi & 0x0F) > 9 || m_RegisterAF.lo & 0x20) {
      m_RegisterAF.hi += 0x06; // Half carry: (9+1) = (0xA+0x6) = 10
      if ((m_RegisterAF.hi & 0xF0) == 0)
        m_RegisterAF.lo |= 0x10;
      else
        m_RegisterAF.lo &= ~0x10;
    }

    if ((m_RegisterAF.hi & 0xF0) > 0x90 || m_RegisterAF.lo & 0x10)
      m_RegisterAF.hi += 0x60;
  }

  if (m_RegisterAF.hi == 0)
    m_RegisterAF.lo |= 0x80;
  else
    m_RegisterAF.lo &= ~0x80;

  return 4;
}

// rotate right through carry
int Emulator::CPU_RR(BYTE &reg) {
  // WHEN EDITING THIS ALSO EDIT CPU_RR_MEMORY

  bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C);
  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (isCarrySet)
    reg = BitSet(reg, 7);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// rotate right through carry
int Emulator::CPU_RR_MEMORY(WORD address) {
  // WHEN EDITING THIS ALSO EDIT CPU_RR

  BYTE reg = ReadMemory(address);

  bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C);
  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (isCarrySet)
    reg = BitSet(reg, 7);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 16;
}

// rotate left
int Emulator::CPU_RLC(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RLC_MEMORY

  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg <<= 1;

  if (isMSBSet) {
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    reg = BitSet(reg, 0);
  }

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// rotate left
int Emulator::CPU_RLC_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RLC

  BYTE reg = ReadMemory(address);

  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg <<= 1;

  if (isMSBSet) {
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    reg = BitSet(reg, 0);
  }

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 16;
}

// rotate right
int Emulator::CPU_RRC(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RRC_MEMORY

  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet) {
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    reg = BitSet(reg, 7);
  }

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// rotate right
int Emulator::CPU_RRC_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RRC

  BYTE reg = ReadMemory(address);

  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet) {
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
    reg = BitSet(reg, 7);
  }

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 15;
}

// shift left arithmetically (basically bit 0 gets set to 0) (bit 7 goes into
// carry)
int Emulator::CPU_SLA(BYTE &reg) {
  // WHEN EDITING THIS ALSO EDIT CPU_SLA_MEMORY

  bool isMSBSet = TestBit(reg, 7);

  reg <<= 1;

  m_RegisterAF.lo = 0;

  if (isMSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

int Emulator::CPU_SLA_MEMORY(WORD address) {
  // WHEN EDITING THIS ALSO EDIT CPU_SLA_MEMORY

  BYTE reg = ReadMemory(address);

  bool isMSBSet = TestBit(reg, 7);

  reg <<= 1;

  m_RegisterAF.lo = 0;

  if (isMSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 16;
}

// shift right. LSB into carry. bit 7 doesn't change
int Emulator::CPU_SRA(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRA_MEMORY

  bool isLSBSet = TestBit(reg, 0);
  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isMSBSet)
    reg = BitSet(reg, 7);
  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// shift right. LSB into carry. bit 7 doesn't change
int Emulator::CPU_SRA_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRA

  BYTE reg = ReadMemory(address);

  bool isLSBSet = TestBit(reg, 0);
  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isMSBSet)
    reg = BitSet(reg, 7);
  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 16;
}

// shift right. bit 0 into carry
int Emulator::CPU_SRL(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRL_MEMORY

  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// shift right. bit 0 into carry
int Emulator::CPU_SRL_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRL

  BYTE reg = ReadMemory(address);

  bool isLSBSet = TestBit(reg, 0);

  m_RegisterAF.lo = 0;

  reg >>= 1;

  if (isLSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 8;
}

// rotate left through carry flag
int Emulator::CPU_RL(BYTE &reg) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RL_MEMORY

  bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C);
  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg <<= 1;

  if (isMSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (isCarrySet)
    reg = BitSet(reg, 0);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  return 8;
}

// rotate left through carry flag
int Emulator::CPU_RL_MEMORY(WORD address) {
  // WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RL

  BYTE reg = ReadMemory(address);

  bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C);
  bool isMSBSet = TestBit(reg, 7);

  m_RegisterAF.lo = 0;

  reg <<= 1;

  if (isMSBSet)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);

  if (isCarrySet)
    reg = BitSet(reg, 0);

  if (reg == 0)
    m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z);

  WriteMemory(address, reg);

  return 16;
}
