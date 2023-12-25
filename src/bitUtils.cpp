#include "bitUtils.h"

bool TestBit(BYTE data, int idx) { return ((data >> idx) & 1) == 1; }

BYTE BitSet(BYTE data, int idx) { return data | (1 << idx); }

BYTE BitReset(BYTE data, int idx) { return ~(BitSet(~data, idx)); }