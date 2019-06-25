#include <stdio.h>
#include <iostream>

int main(int argc, char ** argv) {
    char * p = NULL;
    p = new char[1024];
    for (int i = 0; i < 1024; ++i) {
        p[i] = 'a';
    }

    return 0;
}
