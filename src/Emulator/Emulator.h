#pragma once

#include <functional>

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
        using OpCodeFunction = std::function<void(word)>;

        byte m_Memory[0xFFF + 1] = { 0 };
        bool m_Display[64 * 32] = { 0 };
        OpCodeFunction m_OpCodeFunctions[0xF + 1] = { 0 };

        struct
        {
            word ProgramCounter = 0x0000;
            word Index = 0x0000;

            constexpr byte MaximumStackCount = 16;

            word Stack[MaximumStackCount] = { 0 };
            sbyte StackPointer = -1;
            byte DelayTimer = 0;
            byte SoundTimer = 0;

            byte Variable[0xF + 1];
        } m_Registers;

        void Run();

    #pragma region
        void OpCode0(word instruction);
        void OpCode1(word instruction);
        void OpCode2(word instruction);
        void OpCode3(word instruction);
        void OpCode4(word instruction);
        void OpCode5(word instruction);
        void OpCode6(word instruction);
        void OpCode7(word instruction);
        void OpCode8(word instruction);
        void OpCode9(word instruction);
        void OpCodeA(word instruction);
        void OpCodeB(word instruction);
        void OpCodeC(word instruction);
        void OpCodeD(word instruction);
        void OpCodeE(word instruction);
        void OpCodeF(word instruction);
    #pragma endregion
    };
}