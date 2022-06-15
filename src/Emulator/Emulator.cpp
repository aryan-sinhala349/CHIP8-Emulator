#include "Emulator/Emulator.h"

#include <random>

namespace CHIP8
{
    Emulator::Emulator()
    {
        //The font used for this emulator
        static constexpr byte font[] =
        {
            0xF0, 0x90, 0x90, 0x90, 0xF0, //0
            0x20, 0x60, 0x20, 0x20, 0x70, //1
            0xF0, 0x10, 0xF0, 0x80, 0xF0, //2
            0xF0, 0x10, 0xF0, 0x10, 0xF0, //3
            0x90, 0x90, 0xF0, 0x10, 0x10, //4
            0xF0, 0x80, 0xF0, 0x10, 0xF0, //5
            0xF0, 0x80, 0xF0, 0x90, 0xF0, //6
            0xF0, 0x10, 0x20, 0x40, 0x40, //7
            0xF0, 0x90, 0xF0, 0x90, 0xF0, //8
            0xF0, 0x90, 0xF0, 0x10, 0xF0, //9
            0xF0, 0x90, 0xF0, 0x90, 0x90, //A
            0xE0, 0x90, 0xE0, 0x90, 0xE0, //B
            0xF0, 0x80, 0x80, 0x80, 0xF0, //C
            0xE0, 0x90, 0x90, 0x90, 0xE0, //D
            0xF0, 0x80, 0xF0, 0x80, 0xF0, //E
            0xF0, 0x80, 0xF0, 0x80, 0x80  //F
        };

        //Store the font in memory
        for (byte i = 0; i < 0x50; i++)
            m_Memory[i] = font[i];

        //Register all the opcode functions
        m_OpCodeFunctions[0x0] = std::bind(&Emulator::OpCode0, this);
        m_OpCodeFunctions[0x1] = std::bind(&Emulator::OpCode1, this);
        m_OpCodeFunctions[0x2] = std::bind(&Emulator::OpCode2, this);
        m_OpCodeFunctions[0x3] = std::bind(&Emulator::OpCode3, this);
        m_OpCodeFunctions[0x4] = std::bind(&Emulator::OpCode4, this);
        m_OpCodeFunctions[0x5] = std::bind(&Emulator::OpCode5, this);
        m_OpCodeFunctions[0x6] = std::bind(&Emulator::OpCode6, this);
        m_OpCodeFunctions[0x7] = std::bind(&Emulator::OpCode7, this);
        m_OpCodeFunctions[0x8] = std::bind(&Emulator::OpCode8, this);
        m_OpCodeFunctions[0x9] = std::bind(&Emulator::OpCode9, this);
        m_OpCodeFunctions[0xA] = std::bind(&Emulator::OpCodeA, this);
        m_OpCodeFunctions[0xB] = std::bind(&Emulator::OpCodeB, this);
        m_OpCodeFunctions[0xC] = std::bind(&Emulator::OpCodeC, this);
        m_OpCodeFunctions[0xD] = std::bind(&Emulator::OpCodeD, this);
        m_OpCodeFunctions[0xE] = std::bind(&Emulator::OpCodeE, this);
        m_OpCodeFunctions[0xF] = std::bind(&Emulator::OpCodeF, this);
    }

    Emulator::~Emulator()
    {

    }

    void Emulator::Run()
    {
        //TODO: Implement loop, sound, display, and keypad
    }

    void Emulator::OpCode0(word instruction)
    {
        //Get extra arguments from the instruction
        word args = instruction & 0xFFF;

        switch (args)
        {
            //CLS
            case 0x0E0:
            {
                //Reset all the bits of the display
                memset(&m_Display, 0, 64 * 32);
                break;
            }

            //RET
            case 0x0EE:
            {
                //Make sure the interpreter is currently in a subroutine
                if (m_Registers.StackPointer < 0)
                    break;

                //Set the program counter to the address at the top of the stack
                m_Registers.ProgramCounter = m_Registers.Stack[m_Registers.StackPointer];

                //Subtract one from the stack pointer
                m_Registers.StackPointer--;

                break;
            }

            //SYS addr
            default:
            {
                //This instruction is ignored by most modern interpreters

                break;
            }
        }
    }

    void Emulator::OpCode1(word instruction)
    {
        //JP addr
        {
            //Get the address
            word args = instruction & 0xFFF;

            //Set the program counter to NNN
            m_Registers.ProgramCounter = args;
        }
    }

    void Emulator::OpCode2(word instruction)
    {
        //CALL addr
        {
            //Check to see if there is space left in the stack
            if (m_Registers.StackPointer >= MaximumStackCount)
                return;

            //Get the address
            word args = instruction & 0xFFF;

            //Increment the stack pointer
            m_Registers.StackPointer++;

            //Put the current program counter on the top of the stack
            m_Registers.Stack[m_Registers.StackPointer] = m_Registers.ProgramCounter;

            //Set the program counter to the address
            m_Registers.ProgramCounter = args;
        }
    }

    void Emulator::OpCode3(word instruction)
    {
        //SE VX, byte
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte nn = args & 0xFF;

            //Get the value in VX
            byte vx = m_Registers.Variable[x];

            //Compare register VX to NN
            if (vx == nn)
            {
                //If they are equal, increment the program counter by 2
                m_Registers.ProgramCounter += 2;
            }
        }
    }

    void Emulator::OpCode4(word instruction)
    {
        //SNE VX, byte
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte nn = args & 0xFF;

            //Get the value in VX
            byte vx = m_Registers.Variable[x];

            //Compare register VX to NN
            if (vx != nn)
            {
                //If they are not equal, increment the program counter by 2
                m_Registers.ProgramCounter += 2;
            }
        }
    }

    void Emulator::OpCode5(word instruction)
    {
        //SE VX, VY
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte y = (args >> 4) & 0xF;

            //Get the values of VX and VY
            byte vx = m_Registers.Variable[x];
            byte vy = m_Registers.Variable[y];

            //Compare the register VX to the register VY
            if (vx == vy)
            {
                //If they are equal, increment the program counter by 2
                m_Registers.ProgramCounter += 2;
            }
        }
    }

    void Emulator::OpCode6(word instruction)
    {
        //LD VX, byte
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte nn = args & 0xFF;

            //Put the value of NN into register VX
            m_Registers.Variable[x] = nn;
        }
    }

    void Emulator::OpCode7(word instruction)
    {
        //ADD VX, byte
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte nn = args & 0xFF;

            //Get the value of VX
            byte vx = m_Registers.Variable[x];

            //Add the value NN to the value of register VX and store the value of VX
            m_Registers.Variable[x] = vx + nn;
        }
    }

    void Emulator::OpCode8(word instruction)
    {
        //Get extra arguments from the instruction
        word args = instruction & 0xFFF;
        byte x = (args >> 8) & 0xF;
        byte y = (args >> 4) & 0xF;

        //Get the values of VX and VY
        byte vx = m_Registers.Variable[x];
        byte vy = m_Registers.Variable[y];

        //Get the specific instruction
        byte specificInstruction = args & 0xF;

        switch (specificInstruction)
        {
            //LD VX, VY
            case 0x0:
            {
                //Store the value of VY into register VX
                m_Registers.Variable[x] = vy;

                break;
            }

            //OR VX, VY
            case 0x1:
            {
                //Perform a bitwise OR on the values in VX and VY, then store the value in VX
                m_Registers.Variable[x] = vx | vy;

                break;
            }

            //AND VX, VY
            case 0x2:
            {
                //Perform a bitwise AND on the values in VX and VY, then store the value in VX
                m_Registers.Variable[x] = vx & vy;

                break;
            }

            //XOR VX, VY
            case 0x3:
            {
                //Perform a bitwise XOR on the values in VX and VY, then store the value in VX
                m_Registers.Variable[x] = vx ^ vy;

                break;
            }

            //ADD VX, VY
            case 0x4:
            {
                //Add the values of VX and VY together
                word result = vx + vy;

                //If the result is greater than 8 bits, set VF to 1, otherwise 0
                bool carry = (result >> 8) & 0xFF;
                m_Registers.Variable[0xF] = carry;

                //Store the lower 8 bits into VX
                m_Registers.Variable[x] = result & 0xFF;

                break;
            }

            //SUB VX, VY
            case 0x5:
            {
                //If VX is greater than VY, set VF to 1, otherwise 0
                bool nBorrow = vx > vy;
                m_Registers.Variable[0xF] = nBorrow;

                //Subtract VY from VX and store it in VX
                m_Registers.Variable[x] = vx - vy;

                break;
            }

            //SHR VX {, VY}
            case 0x6:
            {
                //Get the least significant bit and store it in VF
                m_Registers.Variable[0xF] = vx & 0x01;

                //Divide VX by 2
                m_Registers.Variable[x] = vx / 2;

                break;
            }

            //SUBN VX, VY
            case 0x7:
            {
                //If VY is greater than VX, set VF to 1, otherwise 0
                bool nBorrow = vy > vx;
                m_Registers.Variable[0xF] = nBorrow;

                //Subtract VX from VY and store it in VX
                m_Registers.Variable[x] = vy - vx;

                break;
            }

            //SHL VX {, VY}
            case 0xE:
            {
                //Get the most significant bit and store it in VF
                m_Registers.Variable[0xF] = (vx >> 7) & 0x01;

                //Multiply VX by 2
                m_Registers.Variable[x] = vx * 2;

                break;
            }

            //No known opcodes
            default
            {
                break;
            }
        }
    }

    void Emulator::OpCode9(word instruction)
    {
        //SNE VX, VY
        {
            //Get extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte y = (args >> 4) & 0xF;

            //Get the values in VX and VY
            byte vx = m_Registers.Variable[x];
            byte vy = m_Registers.Variable[y];

            //Compare the variables of VX and VY
            if (vx != vy)
            {
                //If they are not equal, increment the program counter by 2
                m_Registers.ProgramCounter += 2;
            }
        }
    }

    void Emulator::OpCodeA(word instruction)
    {
        //LD I, addr
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;

            //Set the value of register I to NNN
            m_Registers.Index = args;
        }
    }

    void Emulator::OpCodeB(word instruction)
    {
        //JP V0, addr
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;

            //Get the value in V0
            byte v0 = m_Registers.Variable[0x0];

            //Set the program counter to V0 + NNN
            m_Registers.ProgramCounter = v0 + args;
        }
    }

    void Emulator::OpCodeC(word instruction)
    {
        //RND VX, byte
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) 0xF;
            word nn = args & 0xFF;

            //The random number generator used
            static std::indepdenent_bits_engine<std::default_random_engine, sizeof(byte) * 8, byte> RNG;

            //The random number generator
            byte result = RNG();

            //Store the result bitwise ANDed with NN and store it in VX
            m_Registers.Variable[x] = result & nn;
        }
    }

    void Emulator::OpCodeD(word instruction)
    {
        //DRAW VX, VY, nibble
        {
            //Get the extra arguments from the instruction
            word args = instruction & 0xFFF;
            byte x = (args >> 8) & 0xF;
            byte y = (args >> 4) & 0xF;
            byte n = args & 0xF;

            //Get the values in VX and VY
            byte vx = m_Registers.Variable[x];
            byte vy = m_Registers.Variable[y];

            //Reset VF
            m_Registers.Variable[0xF] = 0x00;

            //Draw each sprite line by line
            for (byte i = 0; i < n; i++)
            {
                //Get the current line of this sprite
                byte currentLine = m_Memory[m_Registers.Index];

                /*
                 * I preferred to use an unrolled loop here, as it tends to be faster. Even if the performance gains are negligible, I prefer to reduce
                 * overhead as much as possible. Sometimes, you are required to use a rolled loop (as seen just a few lines earlier), but in general,
                 * you should try to unroll your loops if performance is your main concern
                 */

                //Draw this line pixel by pixel
                bool currentPixel = false;
                byte coordinate = 0;

                //8
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 7) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //7
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 6) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //6
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 5) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //5
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 4) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //4
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 3) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //3
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 2) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //2
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = (currentLine >> 1) & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }

                //1
                {
                    //Determine whether or not to flip the current pixel
                    currentPixel = currentLine & 0x01;

                    //The screen coordinate to look at
                    coordinate = (vx + j) + (vy + 32 * n);

                    //Make sure this coordinate is actually on screen
                    if (coordinate >= 64 * 32)
                        return;

                    //Check if there will be a collision
                    if (m_Display[coordinate] && currentPixel)
                        m_Registers.Variable[0xF] = 0x01;

                    //Flip this screen coordinate
                    m_Display[coordinate] = m_Display[coordinate] != currentPixel;
                }
            }
        }
    }

    void Emulator::OpCodeE(word instruction)
    {
        //Get extra arguments from the instruction
        word args = instruction & 0xFFF;
        byte x = (args >> 8) & 0xF;

        //Get the value of VX
        byte vx = m_Registers.Variable[x];

        //Get the specific instruction
        byte specificInstruction = args & 0xFF;

        switch (specificInstruction)
        {
            //SKP VX
            case 0x9E:
            {
                //Check the current state of the key
                //TODO: Implement keypad
                bool keyPressed = false;

                //If the key is pressed
                if (keyPressed)
                {
                    //Increment the program counter by 2
                    m_Registers.ProgramCounter += 2;
                }

                break;
            }

            //SKNP VX
            case 0xA1:
            {
                //Check the current state of the key
                //TODO: Implement keypad
                bool keyPressed = false;

                //If they key is pressed
                if (!keyPressed)
                {
                    //Increment the program counter by 2
                    m_Registers.ProgramCounter += 2;
                }
            }

            //No known opcodes
            default
            {
                break;
            }
        }
    }

    void Emulator::OpCodeF(word instruction)
    {
        //Get extra arguments from the instruction
        word args = instruction & 0xFFF;
        byte x = (args >> 8) & 0xF;

        //Get the value of VX
        byte vx = m_Registers.Variable[x];

        //Get the specific instruction
        byte specificInstruction = args & 0xFF;

        switch (specificInstruction)
        {
            //LD VX, DT
            case 0x07:
            {
                //Place the value of the delay timer into VX
                m_Registers.Variable[x] = m_Registers.DelayTimer;

                break;
            }

            //LD VX, K
            case 0x0A:
            {
                //Get the currently pressed key
                //TODO: Implement keypad
                sbyte pressedKey = 0;

                //If there is a pressed key
                if (pressedKey >= 0x0)
                {
                    //Store the pressed key in VX
                    m_Registers.Variable[x] = pressedKey;

                    break;
                }
                
                //Halt execution otherwise
                m_Registers.ProgramCounter -= 2;

                break;
            }

            //LD DT, VX
            case 0x15:
            {
                //Set the delay timer to the value in VX
                m_Registers.DelayTimer = vx;

                break;
            }

            //LD ST, VX
            case 0x18:
            {
                //Set the sound timer to the value in VX
                m_Registers.SoundTimer = vx;

                break;
            }

            //ADD I, VX
            case 0x1E:
            {
                //Set the value of the index register to the sum of itself and VX
                m_Registers.Index = m_Registers.Index + vx;

                break;
            }

            //LD F, VX
            case 0x29:
            {
                //Set the index register to the location for the hexadecimal sprite corresponding to VX
                m_Registers.Index = 5 * vx;

                break;
            }

            //LD B, VX
            case 0x33:
            {
                //Store the ones digit of vx in index + 2
                m_Memory[m_Registers.Index + 2] = vx % 10;

                //Store the tens digit of vx in index + 1
                vx /= 10;
                m_Memory[m_Registers.Index + 1] = vx % 10;

                //Store the hundreds digit of vx in index
                vx /= 10;
                m_Memory[m_Registers.Index + 0] = vx % 10;

                break;
            }

            //LD [I], VX
            case 0x55:
            {
                //Go through all the values between 0 and x (inclusive)
                for (byte i = 0; i <= x; i++)
                {
                    //Get the value of the current variable register
                    byte vi = m_Registers.Variable[i];

                    //Store the value of VI in memory at index + i
                    m_Memory[m_Registers.Index + i] = vi;
                }

                break;
            }

            //LD VX, [I]
            case 0x65:
            {
                //Go through all the values between 0 and x (inclusive)
                for (byte i = 0; i <= x; i++)
                {
                    //Store the value at memory location index + i in vi
                    m_Registers.Variable[i] = m_Memory[m_Registers.Index + i];
                }

                break;
            }

            //No known opcodes
            default
            {
                break;
            }
        }
    }
}