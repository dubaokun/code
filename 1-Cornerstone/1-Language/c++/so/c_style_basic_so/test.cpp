#include <stdio.h>
//#include <boost/thread/thread.hpp> 
#include "max.h"

int main(int argc, char *argv[])
{
    int a = 10, b = -2, c = 100;
    printf("max among 10, -2 and 100 is %d.\n", max(a, b, c));
    return 0;
}