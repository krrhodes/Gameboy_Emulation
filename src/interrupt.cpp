#include "interrupt.h"

void Emulator::DoInterrupts() {
  if (m_InterruptMaster == true) {
    BYTE req = ReadMemory(0xFF0F);
    BYTE enabled = ReadMemory(INTERRUPT_ENABLED_REGISTER);
    if (req > 0) {
      for (int i = 0; i < 5; i++) {
        if (TestBit(req, i) == true) {
          if (TestBit(enabled, i))
            ServiceInterrupt(i);
        }
      }
    }
  }
}

void Emulator::RequestInterrupt(int id) {
  BYTE req = ReadMemory(0xFF0F);
  req = BitSet(req, id);
  WriteMemory(0xFF0F, id);
}

void Emulator::ServiceInterrupt(int interrupt) {
  m_InterruptMaster = false;
  BYTE req = ReadMemory(0xFF0F);
  req = BitReset(req, interrupt);
  WriteMemory(0xFF0F, req);

  /// we must save the current execution address by pushing it onto the stack
  PushWordOntoStack(m_ProgramCounter);

  switch (interrupt) {
  case 0:
    m_ProgramCounter = 0x40;
    break;
  case 1:
    m_ProgramCounter = 0x48;
    break;
  case 2:
    m_ProgramCounter = 0x50;
    break;
  case 4:
    m_ProgramCounter = 0x60;
    break;
  }
}
