#include "max.h"

int max(int n1, int n2, int n3)
{
    int max_num = n1;
    max_num = max_num < n2? n2: max_num;
    max_num = max_num < n3? n3: max_num;
    char * p = 0x00;
    *p = 0;
    return max_num;
}
