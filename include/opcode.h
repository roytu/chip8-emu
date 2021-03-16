
#pragma once

struct OpcodeParams {
    uint16_t N;
    uint8_t X;
    uint8_t Y;
};

bool opcodeParse(OpcodeParams* res, const char fmt[4], uint16_t op) {
    res->N = 0;
    res->X = 0;
    res->Y = 0;
    for (int i = 0; i < 4; i++) {
        uint8_t c = (op >> ((3 - i) * 4)) & 0xF;
        if ('0' <= fmt[i] && fmt[i] <= 'F') {
            // Hexadecimal literal
            if (fmt[i] - '0' != c) {
                return false;
            }
        } else if (fmt[i] == 'N') {
            // N
            res->N = (res->N << 4) | c;
        } else if (fmt[i] == 'X') {
            // X
            res->X = c;
        } else if (fmt[i] == 'Y') {
            // Y
            res->Y = c;
        }
    }
    return true;
}
