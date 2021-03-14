
#include <stdio.h>
#include "screen.h"

Screen::Screen() {
    for (int r = 0; r < Screen::H; r++) {
        for (int c = 0; c < Screen::W; c++) {
            buffer[r][c] = false;
        }
    }
}

void Screen::print() {
    for (int r = 0; r < Screen::H; r++) {
        for (int c = 0; c < Screen::W; c++) {
            if (buffer[r][c]) {
                printf("x");
            } else {
                printf(" ");
            }
        }
    printf("\n");
    }
}
