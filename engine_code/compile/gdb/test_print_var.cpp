#include <stdio.h>

int main(int argc, char ** argv)
{
    int i = 0;
    char a[100];

    for (i = 0; i < sizeof(a); i++) {
        a[i] = i;
     }

    return 0;
}
