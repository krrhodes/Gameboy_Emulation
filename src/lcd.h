#ifndef GAMEBOY_EMULATION_LCD_H
#define GAMEBOY_EMULATION_LCD_H

#include "emulator.h"

#define LCD_CONTROL ReadMemory(0xFF40)

#define WHITE 00
#define LIGHT_GRAY 01
#define DARK_GRAY 10
#define BLACK 11

#endif // GAMEBOY_EMULATION_LCD_H
