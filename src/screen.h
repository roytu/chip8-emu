
#ifndef SCREEN_H
#define SCREEN_H

class Screen {
    private:
        const static int W = 64;
        const static int H = 32;

        bool buffer[W][H];

    public:
        Screen();
        void print();
};

#endif
