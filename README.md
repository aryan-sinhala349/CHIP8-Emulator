# CHIP8 Emulator
A CHIP8 Emulator to learn emulator development and application development.

# Specifications
- **Memory**
    - `4 kilobytes`
    - Direct Access
    - All the memory is RAM and should be considered writable
    - **Memory Map**
<table border=1>
    <tr>
        <td><code>0x200</code> to <code>0xFFF</code> CHIP-8 Program / Data Space<br/><code>0x200</code> Start of most CHIP-8 programs</td>
    </tr>
    <tr>
        <td><code>0x000</code> to <code>0x1FF</code> reserved for the interpreter</td>
    </tr>
</table>

- **Display**
    - `64 x 32 pixels`
    - Monochrome
    - Each pixel can be turned *on* or *off*
        - Each pixel is a `bool`
- **Program Counter**
    - Often called `PC`
    - Points to the current instruction in memory
- **Index Register**
    - Often called `I`
    - `16-bit`
    - Points at locations in memory
    - Can only address `12` bits
- **Stack**
    - `16-bit` addresses
    - Used to call subroutines/functions and return from them
    - "Last in, first out"
    - At least `16` `two-byte` entries
    - Can unlimit the stack, or limit it to prevent stack overflow errors
- **Delay Timer**
    - `8-bit`
    - Decremented at a rate of `60 Hz` until it reaches `0`
    - Independent of the speed of the fetch/decode/execute loop
    - Interpreter should run as normal while this is being decremented
- **Sound Timer**
    - `8-bit`
    - Functions like the delay timer
    - Gives off a beeping sound as long as it's not `0`
- **General Purpose Variable Registers**
    - 8-bit
    - 16, often numbered `0` through `F` in hexadecimal, `0` through `15` in decimal
    - Often called "`V0`" through "`VF`"
    - "`VF`" is also used as a flag register
- **Font**
    - There should be a built in font
    - Sprite data represents hexadecimal numbers from `0` to `F`
    - Each character is `4 x 5 pixels`
    - Font sprites are drawing just like regular sprites
    - Should be stored in memory
    - Most popular font looks like this:
        ```cpp
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
        ```
- **Keypad**
    - Hexadecimal Keypad
    - `16 keys`, labeled `0` through `F`, arranged in a `4 x 4 grid`
    - Most common layout:
        <table border=1>
            <tr>
                <td><code>1</code></td>
                <td><code>2</code></td>
                <td><code>3</code></td>
                <td><code>C</code></td>
            </tr>
            <tr>
                <td><code>4</code></td>
                <td><code>5</code></td>
                <td><code>6</code></td>
                <td><code>D</code></td>
            </tr>
            <tr>
                <td><code>7</code></td>
                <td><code>8</code></td>
                <td><code>9</code></td>
                <td><code>E</code></td>
            </tr>
            <tr>
                <td><code>A</code></td>
                <td><code>0</code></td>
                <td><code>B</code></td>
                <td><code>F</code></td>
            </tr>
        </table>
- **Fetch/Decode/Execute Loop**
    - **Fetch** the instruction from memory at the current `PC`
        - Read the instruction that `PC` is currently pointing at from memory
        - Instructions are two bytes, so read two successive bytes from memory and combine into one 16-bit instruction
        - Increment `PC` by `2` to prepare for the next opcode
    - **Decode** the instruction to find out what the emulator should do
        - Instructions are divided into broad categories by the first nibble
        - The rest of the nibbles will have different meanings
            - `X`: The second nibble. Used to look up one of the 16 variable registers (`VX`)
            - `Y`: The third nibble. Use to look up one of the 16 variable registers (`VY`)
            - `N`: The fourth nibble. An immediate 4-bit number.
            - `NN`: The second byte (third and fourth nibbles). An immediate 8-bit number.
            - `NNN`: The second, third, and fourth nibbles. An immediate 12-bit memory address
    - **Execute** the instruction and do what it tells you
        - Can use a `switch` to determine how to execute
        - Could also use an array of function pointers or `std::function`s to do this.
- **Timing**
    - Original CHIP8 ran at `1 MHz`
    - HP48 calculators ran at around `4 MHz`
    - Likely want to make the clock speed configurable
    - A standard speed of about 700 instruction per second fits well enough for most programs
- **Instructions**
    - `00E0` - `CLS`
        - Clear the display
    - `00EE` - `RET`
        - Return from a subroutine
        - The interpreter sets the program counter to the address at the top of the stack, then subtracts 1 from the stack pointer
    - `0NNN` - `SYS addr`
        - Jump to a machine code routine at `NNN`
        - This instruction is only used on old computers
        - It is ignored by modern interpeters
    - `1NNN` - `JP addr`
        - Jump to location `NNN`
        - The interpreter sets the program counter to `NNN`
    - `2NNN` - `CALL addr`
        - Call subroutine at `NNN`
        - The interpreter increments the stack pointer, then puts the current `PC` on top of the stack. The `PC` is then set to `NNN`.
    - `3XNN` - `SE VX, byte`
        - Skip next instruction if `VX == NN`
        - The interpreter compares register `VX` to `NN`, and if they are equal, increments the program counter by 2
    - `4XNN` - `SNE VX, byte`
        - Skip next instruction if `VX != NN`
        - The interpreter compares register `VX` to `NN`, and if they are not equal, increments the program counter by 2
    - `5XY0` - `SE VX, VY`
        - Skip next instruction if `VX == VY`
        - The interpreter compares register `VX` to register `VY`, and if they are equal, increments the program counter by 2
    - `6XNN` - `LD VX, byte`
        - Set `VX = NN`
        - The interpreter puts the value `NN` into register `VX`
    - `7XNN` - `ADD VX, byte`
        - Set `VX = VX + NN`
        - Adds the value `NN` to the value of register `VX`, then stores the result in `VX`
    - `8XY0` - `LD VX, VY`
        - Set `VX = VY`
        - Stores the value of register `VY` in register `VX`
    - `8XY1` - `OR VX, VY`
        - Set `VX = VX | VY`
        - Performs a bitwise `OR` on the values of `VX` and `VY`, then stores the result in `VX`
    - `8XY2` - `AND VX, VY`
        - Set `VX = VX & VY`
        - Performs a bitwise `AND` on the values of `VX` and `VY`, then stores the result in `VX`
    - `8XY3` - `XOR VX, Vy`
        - Set `VX = VX ^ VY`
        - Performs a bitwise `XOR` on the values of `VX` and `VY`, then stores the result in `VY`
    - `8XY4` - `ADD VX, VY`
        - Set `VX = VX + VY`, set `VF = carry`
        - The values of `VX` and `VY` are added together
        - If the result is greater than 8 bits, `VF` is set to 1, otherwise 0
        - Only the lower 8 bits of the result are kept, and stored in `VX`
    - `8XY5` - `SUB VX, VY`
        - Set `VX = VX - VY`, set `VF = NOT borrow`
        - If `VX > VY`, then `VF` is set to 1, otherwise 0
        - `VY` is subtracted from `VX`, and the result are stored in `VX`
    - `8XY6` - `SHR VX {, VY}`
        - Set `VX = VX >> 1`
        - If the least-significant bit of `VX` is 1, then `VF`is set to 1, otherwise 0
        - `VX` is divided by 2
    - `8XY7` - `SUBN VX, VY`
        - Set `VX = VY - VX`, set `VF = NOT borrow`
        - If `VY > VX`, then `VF` is set to 1, otherwise 0
        - `VX` is subtracted from `VY`, and the results are stored in `VX`
    - `8XYE` - `SHL VX {, VY}`
        - Set `VX = VX << 1`
        - If the most significant bit of `VX` is 1, then `VF` is set to 1 otherwise 0
        - `VX` is multiplied by 2
    - `9XY0` - `SNE VX, VY`
        - Skip the next instruction if `VX != VY`
        - The values of `VX` and `VY` are compared, and if they are not equal, the program counter is increased by 2
    - `ANNN` - `LD I, addr`
        - The value of register `I` is set to `NNN`
    - `BNNN` - `JP V0, addr`
        - Jump to location `NNN + V0`
        - The program counter is set to `NNN` plus the value of `V0`
    - `CXNN` - `RND VX, byte`
        - Set `VX = random byte & NN`
        - The interpreter generates a random number between 0 and 255, which is then `AND`ed with `NN`
        - The results are stored in `VX`
    - `DXYN` - `DRW VX, VY, nibble`
        - Display `N` byte sprite starting at memory location `I` at (`VX`, `VY`), set `VF = collision`
        - The interpreter reads `N` bytes from memory, starting at the address stored in `I`
        - These bytes are then displayed as sprites on screen at coordinates (`VX`, `VY`)
        - Sprites are `XOR`ed onto the existing screen
        - If this causes any pixels to be erased, `VF` is set to 1, otherwise it is set to 0
        - If the sprite is positioned so part of it is outside the coordinates of the display, it wraps around to the opposite side of the screen
    - `EX9E` - `SKP VX`
        - Skip next instruction if key with the value of `VX` is pressed
        - Checks the keyboard, and if the key corresponding to the value of `VX` is currently in the down position, `PC` is increased by 2
    - `EXA1` - `SKNP VX`
        - Skip next instruction if key with the value of `VX` is not pressed
        - Checks the keyboard, and if the key corresponding to the value of `VX` is currently in the up position, `PC` is increased by 2
    - `FX07` - `LD VX, DT`
        - Set `VX = delay timer value`
        - The value of `DT` is placed into `VX`
    - `FX0A` - `LD VX, K`
        - Wait for a key press, store the value of the key in `VX`
        - All execution stops until a key is pressed, then the value of that key is stored in `VX`.
    - `FX15` - `LD DT, VX`
        - Set `delay timer = VX`
        - `DT` is set to the value of `VX`
    - `FX18` - `LD ST, VX`
        - Set `sound timer = VX`
        - `ST` is set to the value of `VX`
    - `FX1E` - `ADD I, VX`
        - Set `I = I + VX`
        - The values of `I` and `VX` are added, and the results are stored in `I`
    - `FX29` - `LD F, VX`
        - Set `I = location of sprite for digit VX`
        - The value of `I` is set to the location for the hexadecimal sprite corresponding to the value of `VX`
    - `FX33` - `LD B, VX`
        - Store `BCD` representation of `VX` in memory locations `I`, `I+1`, and `I+2`
        - The interpreter takes the decimal value of `VX`, and places the hundreds digit in memory at location in `I`, the tens digit at location `I+1`, and the ones digit at location `I+2`
    - `FX55` - `LD [I], VX`
        - Stores registers `V0` through `VX` in memory starting at location `I`
        - The interpreter copies the values of registers `V0` through `VX` into memory, starting at address in `I`
    - `FX65` - `LD VX, [I]`
        - Read registers `V0` through `VX` from memory starting at location `I`
        - The interpreter reads values from memory starting at location `I` into registers `V0` through `VX`

# Bibliography
- [Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM)
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator)