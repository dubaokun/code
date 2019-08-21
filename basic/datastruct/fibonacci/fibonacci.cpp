// fibonacci function
// recursion type:
// circulation type:

#include <stdio.h>
#include <iostream>

int CirculationFibonacci(int step) {
    if (1 == step || 2 == step) {
        return step;
    }
    
    int first = 0;
    int second = 1;
    int count = 0;
    for (int i = 3; i <= step; ++i) {
        count = first + count;
        first = second;
        second = count;  
    }

    return count;
}
