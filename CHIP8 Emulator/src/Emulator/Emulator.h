#pragma once

#include <cstdint>

#include <SDL.h>

class Emulator
{
public:
    Emulator();

    void Update();

private:
    //Memory
    uint8_t m_RAM[0x1000];
    
    //Registers
    uint8_t m_Variable[0x10] = { 0 }; 
    uint16_t m_Index = 0x0000;
    uint8_t m_Delay = 0x00;
    uint8_t m_Sound = 0x00;
    uint16_t m_ProgramCounter = 0x0000;
    uint8_t m_StackPointer = 0x00;
    uint16_t m_Stack[0x10] = { 0 };

    //Display
    bool m_Display[0x800] = { 0 };

    SDL_Window* m_Window;
    SDL_Renderer* m_Renderer;

    void Step();
    void Render();
};