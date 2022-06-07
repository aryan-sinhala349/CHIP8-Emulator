# CHIP8 Emulator
A CHIP8 Emulator to learn emulator development and application development.

# Specifications
- **Memory**
    - `4 kilobytes`
    - Direct Access
    - All the memory is RAM and should be considered writable
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
        <table>
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

# Bibliography
- [Guide to making a CHIP-8 emulator](https://tobiasvl.github.io/blog/write-a-chip-8-emulator)