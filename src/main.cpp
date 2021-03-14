
#include <iostream>
#include "state.h"

using namespace std;

int main() {
    State state;
    state.loadRom("roms/Pong (1 player).ch8");
    state.run();
}
