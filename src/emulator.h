#ifndef GAMEBOY_EMULATION_EMULATOR_H
#define GAMEBOY_EMULATION_EMULATOR_H

#include <iostream>

//#ifdef WIN32
//#include <Windows.h>
//#include "SDL.h"
//#include "SDL_opengl.h"
//#else
//#include "SDL.h"
//#include "SDL_opengl.h"
//#endif

#include "bitUtils.h"
#include "lcd.h"
#include "register.h"


#define MAX_CYCLES 69905
#define COLOUR BYTE
#define WINDOW_WIDTH 160
#define WINDOW_HEIGHT 144

union Register {
    WORD reg;

    // Little endian
    struct {
        BYTE lo;
        BYTE hi;
    };
};

void InitWindow();

class Emulator {
public:
  Emulator();

  void Update();

private:
  BYTE m_CartridgeMemory[0x200000];

  // [x-coordinate][y-coordinate][red|green|blue]
  BYTE m_ScreenData[160][144][3];
  BYTE m_ScanlineCounter;

  WORD m_ProgramCounter;
Register m_StackPointer;

    Register m_RegisterAF;
    Register m_RegisterBC;
    Register m_RegisterDE;
    Register m_RegisterHL;
  int m_DividerCounter;
  int m_DividerRegister;

  int m_TimerCounter;

  bool m_InterruptMaster;

  BYTE m_Rom[0x10000];
  bool m_MBC1;
  bool m_MBC2;
  BYTE m_CurrentROMBank;
  bool m_ROMBanking;

  BYTE m_RAMBanks[0x8000];
  BYTE m_CurrentRAMBank;
  bool m_EnableRAM;

  BYTE m_JoypadState;

  void InitRegisters();
  void DoDividerRegister(int cycles);

  void LoadCartridge();

  void InitTimerCounter();
  void UpdateTimers(int cycles);
  bool IsClockEnabled() const;
  BYTE GetClockFreq() const;
  void SetClockFreq();

  void InitGraphics();
  void UpdateGraphics(int cycles);
  void SetLCDStatus();
  bool IsLCDEnabled() const;
  void DrawScanLine();
  void RenderTiles();
  void RenderSprites();
  BYTE GetColour(BYTE colourNum, WORD address) const;

  void DoInterrupts();
  void RequestInterrupt(int id);
  void ServiceInterrupt(int interrupt);

  void RenderScreen();

  void InitROM();
  void InitRAM();
  void DetectRomBankMode();
  BYTE ReadMemory(WORD address) const;
  void WriteMemory(WORD address, BYTE data);
  void HandleBanking(WORD address, BYTE data);
  void DoRAMBankEnable(WORD address, BYTE data);
  void DoChangeLoROMBank(BYTE data);
  void DoChangeHiRomBank(BYTE data);
  void DoRAMBankChange(BYTE data);
  void DoChangeROMRAMMode(BYTE data);
  void DoDMATransfer(BYTE data);

  void initJoypad();
  BYTE GetJoypadState() const;
  void KeyPressed(int key);
  void KeyReleased(int key);

  WORD ReadWord() const;
  void PushWordOntoStack(WORD word);
  WORD PopWordOffStack( );

  int ExecuteNextOpcode();
  int ExecuteOpcode(BYTE opcode);
  int ExecuteExtendedOpcode();

  int CPU_8BIT_LOAD(BYTE &reg);
  int CPU_16BIT_LOAD(WORD &reg);
  int CPU_REG_LOAD(BYTE &reg, BYTE load, int cycles);
  int CPU_REG_LOAD_ROM(BYTE &reg, WORD address);
  int CPU_8BIT_ADD(BYTE &reg, BYTE toAdd, int cycles, bool useImmediate,
                    bool addCarry);
  int CPU_8BIT_SUB(BYTE &reg, BYTE toSubtract, int cycles, bool useImmediate,
                    bool subCarry);
  int CPU_8BIT_AND(BYTE &reg, BYTE toAnd, int cycles, bool useImmediate);
  int CPU_8BIT_OR(BYTE &reg, BYTE toOr, int cycles, bool useImmediate);
  int CPU_8BIT_XOR(BYTE &reg, BYTE toXOr, int cycles, bool useImmediate);
  int CPU_8BIT_COMPARE(BYTE reg, BYTE toSubtract, int cycles,
                        bool useImmediate); // dont pass a reference
  int CPU_8BIT_INC(BYTE &reg, int cycles);
  int CPU_8BIT_DEC(BYTE &reg, int cycles);
  int CPU_8BIT_MEMORY_INC(WORD address, int cycles);
  int CPU_8BIT_MEMORY_DEC(WORD address, int cycles);
  int CPU_RESTARTS(BYTE n);

  int CPU_16BIT_DEC(WORD &word, int cycles);
  int CPU_16BIT_INC(WORD &word, int cycles);
  int CPU_16BIT_ADD(WORD &reg, WORD toAdd, int cycles);

  int CPU_JUMP(bool useCondition, int flag, bool condition);
  int CPU_JUMP_IMMEDIATE(bool useCondition, int flag, bool condition);
  int CPU_CALL(bool useCondition, int flag, bool condition);
  int CPU_RETURN(bool useCondition, int flag, bool condition);

  int CPU_SWAP_NIBBLES(BYTE &reg);
  int CPU_SWAP_NIB_MEM(WORD address);
  int CPU_SHIFT_LEFT_CARRY(BYTE &reg);
  int CPU_SHIFT_LEFT_CARRY_MEMORY(WORD address);
  int CPU_SHIFT_RIGHT_CARRY(BYTE &reg, bool resetMSB);
  int CPU_SHIFT_RIGHT_CARRY_MEMORY(WORD address, bool resetMSB);

  int CPU_RESET_BIT(BYTE &reg, int bit);
  int CPU_RESET_BIT_MEMORY(WORD address, int bit);
  int CPU_TEST_BIT(BYTE reg, int bit, int cycles);
  int CPU_SET_BIT(BYTE &reg, int bit);
  int CPU_SET_BIT_MEMORY(WORD address, int bit);

  int CPU_DAA();

  int CPU_RLC(BYTE &reg);
  int CPU_RLC_MEMORY(WORD address);
  int CPU_RRC(BYTE &reg);
  int CPU_RRC_MEMORY(WORD address);
  int CPU_RL(BYTE &reg);
  int CPU_RL_MEMORY(WORD address);
  int CPU_RR(BYTE &reg);
  int CPU_RR_MEMORY(WORD address);

  int CPU_SLA(BYTE &reg);
  int CPU_SLA_MEMORY(WORD address);
  int CPU_SRA(BYTE &reg);
  int CPU_SRA_MEMORY(WORD address);
  int CPU_SRL(BYTE &reg);
  int CPU_SRL_MEMORY(WORD address);
};

#endif // GAMEBOY_EMULATION_EMULATOR_H
