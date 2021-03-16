#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "screen.h"
#include "state.h"
#include "opcode.h"
#include "util.h"

using namespace std;

State::State() {
    for(int i = 0; i < 16; i++) {
        regs[i] = 0x0000;
    }

    for(int i = 0; i < 4096; i++) {
        mem[i] = 0;
    }

    pc = 512;
};

void State::step() {
    // Get current opcode
    uint16_t op = mem[pc];

    OpcodeParams params;
    
    if (opcodeParse(&params, "0NNN", op)) {
        // 0NNN: Unsupported
        pc += 2;
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "00E0", op)) {
        // 00E0: Clear the screen
        pc += 2;
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "00EE", op)) {
        // 00EE: Return from subroutine
        pc += 2;
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "1NNN", op)) {
        // 1NNN: Jumps to address NNN.
        pc = params.N;
    } else if (opcodeParse(&params, "2NNN", op)) {
        // 2NNN: Call subroutine at NNN
        cout << "Not implemented" << endl;
        pc += 2;
    } else if (opcodeParse(&params, "3XNN", op)) {
        // 3XNN: Skip next instruction if Vx == NN
        cout << "Not implemented" << endl;
        pc += 2;
    } else if (opcodeParse(&params, "4XNN", op)) {
        // 4XNN: Skip next instruction if Vx != NN
        cout << "Not implemented" << endl;
        pc += 2;
    } else if (opcodeParse(&params, "5XY0", op)) {
        // 5XY0: Skip next instruction if Vx != Vy
        cout << "Not implemented" << endl;
        pc += 2;
    } else if (opcodeParse(&params, "6XNN", op)) {
        // 6XNN: Sets Vx = NN
        regs[params.X] = params.N;
        pc += 2;
    } else if (opcodeParse(&params, "7XNN", op)) {
        // 7XNN: Adds NN to Vx (don't update carry flag)
        regs[params.X] += params.N;
        pc += 2;
    } else if (opcodeParse(&params, "8XY0", op)) {
        // 8XY0: Sets Vx = Vy
        regs[params.X] = regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY1", op)) {
        // 8XY1: Sets Vx = Vx | Vy
        regs[params.X] |= regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY2", op)) {
        // 8XY2: Sets Vx = Vx & Vy
        regs[params.X] &= regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY3", op)) {
        // 8XY3: Sets Vx = Vx ^ Vy
        regs[params.X] ^= regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY4", op)) {
        // 8XY4: Vx += Vy
        // VF is set to 1 when there's a carry, and to 0 when there isn't.
        if ((uint32_t)Vx + (uint32_t)(Vy) > 0xFFFF) {
            regs[0xF] = 1;
        } else {
            regs[0xF] = 0;
        }
        regs[params.X] += regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY5", op)) {
        // 8XY5: Vx -= Vy
        // VF is set to 0 when there's a borrow, and 1 when there isn't.
        if (Vx < Vy) {
            regs[0xF] = 0;
        } else {
            regs[0xF] = 1;
        }
        regs[params.X] -= regs[params.Y];
        pc += 2;
    } else if (opcodeParse(&params, "8XY6", op)) {
        // 8XY6: Stores the least significant bit of VX in VF and then shifts VX to the right by 1
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "8XY7", op)) {
        // 8XY7: Sets VX to VY minus VX. VF is set to 0 when there's a borrow, and 1 when there isn't.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "8XYE", op)) {
        // 8XYE: Stores the most significant bit of VX in VF and then shifts VX to the left by 1.[b]
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "9XY0", op)) {
        // 9XY0: Skips the next instruction if VX doesn't equal VY. (Usually the next instruction is a jump to skip a code block)
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "ANNN", op)) {
        // ANNN: Sets I to the address NNN.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "BNNN", op)) {
        // BNNN: Jumps to the address NNN plus V0.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "CXNN", op)) {
        // CXNN: Sets VX to the result of a bitwise and operation on a random number (Typically: 0 to 255) and NN.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "DXYN", op)) {
        // DXYN: Draws a sprite at coordinate (VX, VY) that has a width of 8 pixels and a height of N+1 pixels. Each row of 8 pixels is read as bit-coded starting from memory location I; I value doesn’t change after the execution of this instruction. As described above, VF is set to 1 if any screen pixels are flipped from set to unset when the sprite is drawn, and to 0 if that doesn’t happen
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "EX9E", op)) {
        // EX9E: Skips the next instruction if the key stored in VX is pressed. (Usually the next instruction is a jump to skip a code block)
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "EXA1", op)) {
        // EXA1: Skips the next instruction if the key stored in VX isn't pressed. (Usually the next instruction is a jump to skip a code block)
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX07", op)) {
        // FX07: Sets VX to the value of the delay timer.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX0A", op)) {
        // FX0A: A key press is awaited, and then stored in VX. (Blocking Operation. All instruction halted until next key event)
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX15", op)) {
        // FX15: Sets the delay timer to VX.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX18", op)) {
        // FX18: Sets the sound timer to VX.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX1E", op)) {
        // FX1E: Adds VX to I. VF is not affected.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX29", op)) {
        // FX29: Sets I to the location of the sprite for the character in VX. Characters 0-F (in hexadecimal) are represented by a 4x5 font.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX33", op)) {
        // FX33: Stores the binary-coded decimal representation of VX, with the most significant of three digits at the address in I, the middle digit at I plus 1, and the least significant digit at I plus 2. (In other words, take the decimal representation of VX, place the hundreds digit in memory at location in I, the tens digit at location I+1, and the ones digit at location I+2.)
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX55", op)) {
        // FX55: Stores V0 to VX (including VX) in memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
        cout << "Not implemented" << endl;
    } else if (opcodeParse(&params, "FX65", op)) {
        // FX65: Fills V0 to VX (including VX) with values from memory starting at address I. The offset from I is increased by 1 for each value written, but I itself is left unmodified.
        cout << "Not implemented" << endl;
    } else {
        // Invalid opcode
        pc += 2;
        cout << "Not implemented" << endl;
    }
}

void State::run() {
    while (true) {
        // Run step
        step();

        // Draw screen
        cout << "BEGIN" << endl;
        screen.print();
        cout << "END" << endl;

        // Print debug info
        print();

        getchar();
    }
}

void State::loadRom(string fname) {
    streampos size;

    ifstream file (fname, ios::in|ios::binary|ios::ate);
    if (file.is_open()) {
        size = file.tellg();
        file.seekg (0, ios::beg);
        file.read((char*)&mem[512], size);
        file.close();
    } else {
        cout << "Cannot find rom" << endl;
    }
}

void State::print() {
    cout << "--- Debug ---" << endl;

    // Registers
    cout << "Regs:" << endl;
    for (int i = 0; i < 16; i++) {
        cout << "V" << dec2hex(i) << "\t\t" << 0 << endl;
    }

    cout << "pc: " << pc << endl;

    // Memory
    cout << "Mem:" << endl;
    stringstream ss;
    //for (int r = 0; r < 128; r++) {
    for (int r = 0; r < 64; r++) {
        ss << short2hex(r * 32) << " | ";
        for (int c = 0; c < 32; c++) {
            //ss << byte2hex(mem[r * 16 + c]) << " ";
            ss << byte2hex(mem[r * 32 + c]) << " ";
        }
        ss << endl;
    }
    cout << ss.str() << endl;

}

