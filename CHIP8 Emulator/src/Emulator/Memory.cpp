#include "Emulator/Memory.h"

#include <iostream>

uint8_t Memory::ReadMemory(uint16_t address)
{
    using std::cerr;
    using std::endl;

    if (address > 0xFFF)
    {
        cerr << "The provided address " << address << " is out of range!" << endl;
        return 0;
    }

    return m_RAM[address];
}

void Memory::WriteMemory(uint16_t address, uint8_t value)
{
    using std::cerr;
    using std::endl;

    if (address > 0xFFF)
    {
        cerr << "The provided address " << address << " is out of range!" << endl;
        return;
    }

    m_RAM[address] = value;
}