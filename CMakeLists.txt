cmake_minimum_required(VERSION 3.27)
project(Gameboy_Emulation)

set(CMAKE_CXX_STANDARD 17)


add_executable(Gameboy_Emulation src/emulator.cpp
        src/emulator.h
        src/register.h
        src/flag.h
        src/timer.cpp
        src/timer.h
        src/memory.cpp
        src/memory.h
        src/register.cpp
        src/interrupt.h
        src/interrupt.cpp
        src/lcd.h
        src/lcd.cpp
        src/joypad.cpp
        src/joypad.h
        src/bitUtils.h
        src/bitUtils.cpp
        src/cpuJumpTable.cpp
        src/cpuJumpTable.h
        src/cpuOpCodes.cpp
        src/cpuOpCodes.h)
