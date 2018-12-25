#include <stdint.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    int16_t a = -1;
    uint16_t b = a;
    uint32_t c = a;

    uint16_t d = static_cast<uint16_t>(a);
    int32_t e = static_cast<uint32_t>(a);

    cout << a << endl;
    cout << b << endl;
    cout << c << endl; 
    cout << d << endl; 
    cout << e << endl; 
}
