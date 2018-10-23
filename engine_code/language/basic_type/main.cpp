#include <stdint.h>
#include <iostream>

using std::cout;

int main(int argc, char ** argv) {
    uint8_t u8 = 0;

    for (int i = 0; i < 1200; ++i) {
        u8 += 1;
        std::cout << (unsigned)u8 << std::endl;
    }

    return 0;
}
