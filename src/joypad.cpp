#include "joypad.h"

void Emulator::initJoypad() { m_JoypadState = 0x0000; }

BYTE Emulator::GetJoypadState() const {
  BYTE res = m_Rom[0xFF00];
  // flip all the bits
  res ^= 0xFF;

  // are we interested in the standard buttons?
  if (!TestBit(res, 4)) {
    BYTE topJoypad = m_JoypadState >> 4;
    topJoypad |= 0xF0;         // turn the top 4 bits on
    res &= topJoypad;          // show what buttons are pressed
  } else if (!TestBit(res, 5)) // directional buttons
  {
    BYTE bottomJoypad = m_JoypadState & 0xF;
    bottomJoypad |= 0xF0;
    res &= bottomJoypad;
  }
  return res;
}

void Emulator::KeyPressed(int key) {
  bool previouslyUnset = false;

  // if setting from 1 to 0 we may have to request an interupt
  if (TestBit(m_JoypadState, key) == false)
    previouslyUnset = true;

  // remember if a keypressed its bit is 0 not 1
  m_JoypadState = BitReset(m_JoypadState, key);

  // button pressed
  bool button = true;

  // is this a standard button or a directional button?
  if (key > 3)
    button = true;
  else // directional button pressed
    button = false;

  BYTE keyReq = m_Rom[0xFF00];
  bool requestInterrupt = false;

  // only request interrupt if the button just pressed is
  // the style of button the game is interested in
  if (button && !TestBit(keyReq, 5))
    requestInterrupt = true;

  // same as above but for directional button
  else if (!button && !TestBit(keyReq, 4))
    requestInterrupt = true;

  // request interrupt
  if (requestInterrupt && !previouslyUnset)
    RequestInterrupt(4);
}

void Emulator::KeyReleased(int key) {
  m_JoypadState = BitSet(m_JoypadState, key);
}