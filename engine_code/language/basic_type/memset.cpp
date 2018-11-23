#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

int main(int argc, char ** argv) {
    int64_t buffer[64];
    memset(buffer, -1, sizeof(buffer));
    for (int i = 0; i < 64; ++i) {
        cout << buffer[i] << endl;
    }
    
    return 0;
}

