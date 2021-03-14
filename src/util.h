
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>

using namespace std;

char dec2hex(int x) {
    const char d2h[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    return d2h[x];
}

string byte2hex(uint8_t x) {
    return dec2hex(x >> 4 & 0xF) + dec2hex(x & 0xF);
}

void clearScreen() {
    cout << string( 100, '\n' );
}

#endif
