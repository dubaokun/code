#include <stdio.h>
#include "crc64.h"
#include <pthread.h>
#include <assert.h>

int a = 0;

void* func(void* arg)
{
    while(1)
    {
        if(a == 1)
        {
            const char* s = "Hello World";
            uint64_t termid = 0;
            crc64(s, strlen(s), &termid);
            assert(termid == 14348400473747635334U);
            printf("hello world = %lu\n", termid);
            break;
        }
    }
}

int main()
{
    printf("main started\n");
    pthread_t threads[10];
    for(int i = 0; i < 10; i++)
    {
        pthread_create(&threads[i], NULL, func, NULL);
    }
    a = 1;
    for(int i = 0; i < 10; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf("all thread runs once\n");

    for(int i = 0; i < 10; i++)
    {   
        pthread_create(&threads[i], NULL, func, NULL);
    }
    return 0;
}
