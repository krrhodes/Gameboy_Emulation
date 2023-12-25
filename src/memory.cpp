#include "memory.h"

void Emulator::InitROM() {
  m_Rom[0xFF05] = 0x00;
  m_Rom[0xFF06] = 0x00;
  m_Rom[0xFF07] = 0x00;
  m_Rom[0xFF10] = 0x80;
  m_Rom[0xFF11] = 0xBF;
  m_Rom[0xFF12] = 0xF3;
  m_Rom[0xFF14] = 0xBF;
  m_Rom[0xFF16] = 0x3F;
  m_Rom[0xFF17] = 0x00;
  m_Rom[0xFF19] = 0xBF;
  m_Rom[0xFF1A] = 0x7F;
  m_Rom[0xFF1B] = 0xFF;
  m_Rom[0xFF1C] = 0x9F;
  m_Rom[0xFF1E] = 0xBF;
  m_Rom[0xFF20] = 0xFF;
  m_Rom[0xFF21] = 0x00;
  m_Rom[0xFF22] = 0x00;
  m_Rom[0xFF23] = 0xBF;
  m_Rom[0xFF24] = 0x77;
  m_Rom[0xFF25] = 0xF3;
  m_Rom[0xFF26] = 0xF1;
  m_Rom[0xFF40] = 0x91;
  m_Rom[0xFF42] = 0x00;
  m_Rom[0xFF43] = 0x00;
  m_Rom[0xFF45] = 0x00;
  m_Rom[0xFF47] = 0xFC;
  m_Rom[0xFF48] = 0xFF;
  m_Rom[0xFF49] = 0xFF;
  m_Rom[0xFF4A] = 0x00;
  m_Rom[0xFF4B] = 0x00;
  m_Rom[0xFFFF] = 0x00;

  m_CurrentROMBank = 1;
}

void Emulator::InitRAM() {
  memset(&m_RAMBanks, 0, sizeof(m_RAMBanks));
  m_CurrentRAMBank = 0;
}

void Emulator::DetectRomBankMode() {
  m_MBC1 = false;
  m_MBC2 = false;

  switch (m_CartridgeMemory[0x147]) {
  case 1:
    m_MBC1 = true;
    break;
  case 2:
    m_MBC1 = true;
    break;
  case 3:
    m_MBC1 = true;
    break;
  case 5:
    m_MBC2 = true;
    break;
  case 6:
    m_MBC2 = true;
    break;
  default:
    break;
  }
}

BYTE Emulator::ReadMemory(WORD address) const {
  // are we reading from the rom memory bank?
  if ((address >= 0x4000) && (address <= 0x7FFF)) {
    WORD newAddress = address - 0x4000;
    return m_CartridgeMemory[newAddress + (m_CurrentROMBank * 0x4000)];
  }

  // are we reading from ram memory bank?
  else if ((address >= 0xA000) && (address <= 0xBFFF)) {
    WORD newAddress = address - 0xA000;
    return m_RAMBanks[newAddress + (m_CurrentRAMBank * 0x2000)];
  }

  else if (0xFF00 == address) {
    return GetJoypadState();
  }

  // else return memory
  return m_Rom[address];
}

void Emulator::WriteMemory(WORD address, BYTE data) {
  /*
  Restrict memory writes based of the following banks:

  0000-3FFF 16KB ROM Bank 00 (in cartridge, fixed at bank 00)
  4000-7FFF 16KB ROM Bank 01..NN (in cartridge, switchable bank number)
  8000-9FFF 8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
  A000-BFFF 8KB External RAM (in cartridge, switchable bank, if any)
  C000-CFFF 4KB Work RAM Bank 0 (WRAM)
  D000-DFFF 4KB Work RAM Bank 1 (WRAM) (switchable bank 1-7 in CGB Mode)
  E000-FDFF Same as C000-DDFF (ECHO) (typically not used)
  FE00-FE9F Sprite Attribute Table (OAM)
  FEA0-FEFF Not Usable
  FF00-FF7F I/O Ports
  FF80-FFFE High RAM (HRAM)
  FFFF Interrupt Enable Register
   */

  if (address < 0x8000) {
    HandleBanking(address, data);
  }

  else if ((address >= 0xA000) && (address < 0xC000)) {
    if (m_EnableRAM) {
      WORD newAddress = address - 0xA000;
      m_RAMBanks[newAddress + (m_CurrentRAMBank * 0x2000)] = data;
    }
  }

  // Writing to ECHO ram also writes in RAM
  else if ((address >= 0xE000) && (address < 0xFE00)) {
    m_Rom[address] = data;
    WriteMemory(address - 0x2000, data);
  }

  // This area is restricted
  else if ((address >= 0xFEA0) && (address < 0xFEFF)) {
  }

  else if (TMC == address) {
    BYTE currentfreq = GetClockFreq();
    m_CartridgeMemory[TMC] = data;
    BYTE newfreq = GetClockFreq();

    if (currentfreq != newfreq) {
      SetClockFreq();
    }
  }

  // trap the divider register
  else if (0xFF04 == address)
    m_Rom[0xFF04] = 0;

  // reset the current scanline if the game tries to write to it
  else if (0xFF44 == address) {
    m_Rom[address] = 0;
  }

  else if (0xFF46 == address) {
    DoDMATransfer(data);
  }

  // No control needed over this area so write to memory
  else {
    m_Rom[address] = data;
  }
}

void Emulator::HandleBanking(WORD address, BYTE data) {
  // do RAM enabling
  if (address < 0x2000) {
    if (m_MBC1 || m_MBC2) {
      DoRAMBankEnable(address, data);
    }
  }

  // do ROM bank change
  else if ((address >= 0x200) && (address < 0x4000)) {
    if (m_MBC1 || m_MBC2) {
      DoChangeLoROMBank(data);
    }
  }

  // do ROM or RAM bank change
  else if ((address >= 0x4000) && (address < 0x6000)) {
    // there is no rambank in mbc2 so always use rambank 0
    if (m_MBC1) {
      if (m_ROMBanking) {
        DoChangeHiRomBank(data);
      } else {
        DoRAMBankChange(data);
      }
    }
  }
  // this will change whether we are doing ROM banking
  // or RAM banking with the above if statement
  else if ((address >= 0x6000) && (address < 0x8000)) {
    if (m_MBC1)
      DoChangeROMRAMMode(data);
  }
}

void Emulator::DoRAMBankEnable(WORD address, BYTE data) {
  if (m_MBC2) {
    if (TestBit(address, 4) == 1)
      return;
  }

  BYTE testData = data & 0xF;
  if (testData == 0xA)
    m_EnableRAM = true;
  else if (testData == 0x0)
    m_EnableRAM = false;
}

void Emulator::DoChangeLoROMBank(BYTE data) {
  if (m_MBC2) {
    m_CurrentROMBank = data & 0xF;
    if (m_CurrentROMBank == 0)
      m_CurrentROMBank++;
    return;
  }

  BYTE lower5 = data & 31;
  m_CurrentROMBank &= 224; // turn off the lower 5
  m_CurrentROMBank |= lower5;
  if (m_CurrentROMBank == 0)
    m_CurrentROMBank++;
}

void Emulator::DoChangeHiRomBank(BYTE data) {
  // turn off the upper 3 bits of the current rom
  m_CurrentROMBank &= 31;

  // turn off the lower 5 bits of the data
  data &= 224;
  m_CurrentROMBank |= data;
  if (m_CurrentROMBank == 0)
    m_CurrentROMBank++;
}

void Emulator::DoRAMBankChange(BYTE data) { m_CurrentRAMBank = data & 0x3; }

void Emulator::DoChangeROMRAMMode(BYTE data) {
  BYTE newData = data & 0x1;
  m_ROMBanking = (newData == 0) ? true : false;
  if (m_ROMBanking)
    m_CurrentRAMBank = 0;
}

void Emulator::DoDMATransfer(BYTE data) {
  WORD address = data << 8; // source address is data * 100
  for (int i = 0; i < 0xA0; i++) {
    WriteMemory(0xFE00 + i, ReadMemory(address + i));
  }
}