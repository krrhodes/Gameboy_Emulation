//
// Created by River Rhodes on 12/24/23.
//

#ifndef GAMEBOY_EMULATION_BITUTILS_H
#define GAMEBOY_EMULATION_BITUTILS_H

typedef unsigned char BYTE;
typedef char SIGNED_BYTE;
typedef unsigned short WORD;
typedef signed short SIGNED_WORD;

bool TestBit(BYTE data, int idx);
BYTE BitSet(BYTE data, int idx);
BYTE BitReset(BYTE data, int idx);

#endif // GAMEBOY_EMULATION_BITUTILS_H
