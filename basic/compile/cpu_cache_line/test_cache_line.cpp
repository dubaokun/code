#include "stdio.h"
#include <stdlib.h>
#include <time.h>

time_t timediff(time_t t1, time_t t2) {
    time_t elapsed;
    elapsed = (t2 - t1);
    return elapsed;
}

int main(int argc, char *argv[])
{

    int array_size=atoi(argv[1]);
    int repeat_times = 1000000000;
    int repeat_times2 = 1000000000;
    long array[array_size];
    for(int i=0; i<array_size; i++){
        array[i] = 0;
    }
    int i = 0;
    int j=0;
    int k=0;
    int c=0;
    time_t start= time(NULL);
    while(i++<repeat_times2){
    while(j++<repeat_times){
        if(k==array_size){
            k=0;
        }
        c = array[k++];
    }
}
    time_t end =time(NULL);
    printf("%lu\n", timediff(start,end));
    return 0;
}

