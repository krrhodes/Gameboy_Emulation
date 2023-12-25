#include "register.h"

void Emulator::InitRegisters() {
  m_RegisterAF.reg = 0x01B0;
  m_RegisterBC.reg = 0x0013;
  m_RegisterDE.reg = 0x00D8;
  m_RegisterHL.reg = 0x014D;
  m_DividerCounter = 0;
  m_DividerRegister = 0x0000;
}

void Emulator::DoDividerRegister(int cycles) {
  m_DividerRegister += cycles;
  if (m_DividerCounter >= 255) {
    m_DividerCounter = 0;
    m_Rom[0xFF04]++;
  }
}