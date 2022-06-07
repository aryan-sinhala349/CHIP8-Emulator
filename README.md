# CHIP8 Emulator
A CHIP8 Emulator to learn emulator development and application development.

# Specifications
- **Memory**
    - 4 kilobytes
    - Direct Access
- **Display**
    - 64x32
    - Monochrome
- **Program Counter**
    - Often called `PC`
    - Points to the current instruction in memory
- **Index Register**
    - Often called `I`
    - 16-bit
    - Points at locations in memory
    - Can only address 12 bits
- **Stack**
    - 16-bit addresses
    - Used to call subroutines/functions and return from them
- **Delay Timer**
    - 8-bit
    - Decremented at a rate of 60 Hz until it reaches zero
- **Sound Timer**
    - 8-bit
    - Functions like the delay timer
    - Gives off a beeping sound as long as it's not 0
- **General Purpose Variable Registers**
    - 8-bit
    - 16, often numbered `0` through `F` in hexadecimal, `0` through `15` in decimal
    - Often called "`V0`" through "`VF`"
    - "`VF`" is also used as a flag register

# Bibliography
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator)