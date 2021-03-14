
#include <iostream>
#include <cstdint>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "screen.h"
#include "state.h"
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
    pc++;
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
        file.read((char*)&mem[0x200], size);
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
    ss << hex;
    //for (int r = 0; r < 128; r++) {
    for (int r = 0; r < 64; r++) {
        for (int c = 0; c < 32; c++) {
            ss << std::setw(2) << std::setfill('0') << hex << (uint8_t)mem[r * 16 + c] << " ";
        }
        ss << endl;
    }
    cout << ss.str() << endl;

}

