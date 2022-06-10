#pragma once

#include "Base.h"

extern int main(int argc, char** argv);

namespace CHIP8
{
    class Emulator
    {
        friend int ::main(int argc, char** argv);

    public:
        Emulator();
        ~Emualtor();

    private:
        byte m_Memory[0xFFF + 1] = { 0 };
        bool m_Display[64 * 32] = { 0 };

        struct
        {
            word ProgramCounter = 0x0000;
            word Index = 0x0000;

            constexpr byte MaximumStackCount = 16;

            word Stack[MaximumStackCount] = { 0 };
            byte StackPointer = 0;
            byte DelayTimer = 0;
            byte SoundTimer = 0;

            byte Variable[0xF + 1];
        } m_Registers;

        void Run();
    };
}