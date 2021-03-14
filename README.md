# chip8-emu
an emulator for chip8 to practice c/c++

roms from https://github.com/kripod/chip8-roms


# Memory Layout

| 0x0000 |                  |
| ------ | ---------------- |
|        |  Interpreter     |
| ------ | ---------------- |
| 0x0200 |                  |
| ------ | ---------------- |
|        |                  |
| ------ | ---------------- |
| 0x0EA0 |                  |
| ------ | ---------------- |
|        |  Call stack      |
| ------ | ---------------- |
| 0x0F00 |                  |
| ------ | ---------------- |
|        |  Display refresh |
| ------ | ---------------- |
| 0x1000 |                  |

# Registers

16 8-bit registers:

* V0 - VF
    * VF doubles as flag for some instructions, so not for general use
* Address register (I)
    * 16-bits wide

# Stack
The stack is only used to store return addresses when subroutines are called.

The original RCA 1802 version allocated 48 bytes for up to 12 levels of
nesting;[12] modern implementations usually have more.[13][14]

# Timers

Two timers:
* Delay timer: Can be set and read
* Sound timer: When non-zero, beep

Both count down at 60 Hz, until they reach 0

# Input
16 inputs, 0 - F

* 2468: directional input
* Three opcodes detect input (see below)

# Graphics

Resolution: 64x32
Color: Monochrome

* Graphics are drawn to the screen solely by drawing sprites.
* Sprites are 8 px wide, from 1-16 px high.
* Sprite pixels are XOR'ed with screen pixels
* The carry flag (VF) is set to 1 if any screen pixels are flipped from set to unset when a sprite is drawn and set to 0 otherwise. This is used for collision detection.

# Sound

Beeps when sound timer is nonzero.

# Opcode table

35 opcodes

* All two bytes long, big-endian

NNN: address
NN: 8-bit constant
N: 4-bit constant
X and Y: 4-bit register identifier
PC : Program Counter
I : 16bit register (For memory address) (Similar to void pointer)
VN: One of the 16 available variables. N may be 0 to F (hexadecimal)
There have been many implementations of the CHIP-8 instruction set since 1978. The following specification is based on the SUPER-CHIP specification from 1991 (but without the additional opcodes that provide extended functionality), as that is the most commonly encountered extension set today. Footnotes denote incompatibilities with the original CHIP-8 instruction set from 1978.
