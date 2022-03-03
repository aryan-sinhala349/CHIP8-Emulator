#pragma once

#include <cstdint>

class Memory
{
public:
    uint8_t ReadMemory(uint16_t address);
    void WriteMemory(uint16_t address, uint8_t value);

private:
    uint8_t m_RAM[0x1000] = { 0 };
};