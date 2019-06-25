#include <stdint.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    uint8_t u8a = 0;
    uint64_t u64a = 65536;
    u8a = (uint8_t)u64a;
    
    cout << u8a << endl;

    return 0;
}
