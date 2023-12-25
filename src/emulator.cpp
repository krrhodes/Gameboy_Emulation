#include "emulator.h"

int main(int argc, char *argv[]) {
  Emulator emulator;
  InitWindow();
  while (true) {
    emulator.Update();
  }
}

Emulator::Emulator() {
  m_ProgramCounter = 0x100;
  m_StackPointer.reg = 0xFFFE;

  InitRegisters();

  InitROM();

  InitRAM();

  LoadCartridge();

  DetectRomBankMode();

  InitTimerCounter();

  InitGraphics();

  initJoypad();
}

void Emulator::LoadCartridge() {
  memset(m_CartridgeMemory, 0, sizeof(m_CartridgeMemory));

  FILE *in;
  std::cout << "loading Pokemon.gb..." << std::endl;
  in = fopen("Pokemon.gb", "rb");
  fread(m_CartridgeMemory, 1, 0x200000, in);
  fclose(in);
}

void Emulator::Update() {
  int cyclesThisUpdate = 0;

  while (cyclesThisUpdate < MAX_CYCLES) {
    int cycles = ExecuteNextOpcode();
    cyclesThisUpdate += cycles;
    UpdateTimers(cycles);
    DoDividerRegister(cycles);
    UpdateGraphics(cycles);
    DoInterrupts();
  }
  RenderScreen();
}

WORD Emulator::ReadWord() const
{
    WORD res = ReadMemory(m_ProgramCounter+1) ;
    res = res << 8 ;
    res |= ReadMemory(m_ProgramCounter) ;
    return res ;
}

void Emulator::PushWordOntoStack(WORD word)
{
    BYTE hi = word >> 8 ;
    BYTE lo = word & 0xFF;
    m_StackPointer.reg-- ;
    WriteMemory(m_StackPointer.reg, hi) ;
    m_StackPointer.reg-- ;
    WriteMemory(m_StackPointer.reg, lo) ;
}

WORD Emulator::PopWordOffStack( )
{
    WORD word = ReadMemory(m_StackPointer.reg+1) << 8 ;
    word |= ReadMemory(m_StackPointer.reg) ;
    m_StackPointer.reg+=2 ;

    return word ;
}

void InitWindow( )
{
//    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
//    {
//        return;
//    } else if( SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 8, SDL_OPENGL ) == NULL )
//    {
//        return;
//    }
//
//    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
//    glMatrixMode(GL_MODELVIEW);
//    glLoadIdentity();
//    glOrtho(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0, -1.0, 1.0);
//    glClearColor(0, 0, 0, 1.0);
//    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//    glShadeModel(GL_FLAT);
//
//    glEnable(GL_TEXTURE_2D);
//    glDisable(GL_DEPTH_TEST);
//    glDisable(GL_CULL_FACE);
//    glDisable(GL_DITHER);
//    glDisable(GL_BLEND);
//
//    SDL_WM_SetCaption( "OpenGL Test", NULL );
}

void Emulator::RenderScreen() {
    std::cout << m_ScreenData << std::endl;
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glRasterPos2i(-1, 1);
//    glPixelZoom(1, -1);
//    glDrawPixels(160, 144, GL_RGB, GL_UNSIGNED_BYTE, m_ScreenData);
//    SDL_GL_SwapBuffers( ) ;
}