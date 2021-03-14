
#include <string>
#include <cstdint>
#include "screen.h"

using namespace std;

class State {

    private:
        uint16_t regs[16];
        uint8_t mem[4096];
        uint32_t pc;
        Screen screen;
    public:
        State();
        void step();
        void run();
        void print();
        void loadRom(string fname);


};
