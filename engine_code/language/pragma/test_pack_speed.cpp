#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

long GetTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    long tt = tv.tv_sec * 1000 + tv.tv_usec / 1000 ;
    return tt;
}
 
int main(int argc, char ** argv)
{
    char buf[512];
    int tmp = 0;
    int count = 100000000;
 
    memset(buf, sizeof(buf), 0);
    long t1 = GetTime();
    for (int i=0; i<count; ++i)
    {
        for (int j=1;j<(sizeof(buf)-4);j+=4)
        {
            tmp = *(int*)&buf[j];
            tmp++;
            *(int*)&buf[j] = tmp;
        }
    }
    long t2 = GetTime();
    printf("use time : %ld\n", t2 - t1);
 
    tmp = 0;
    memset(buf, sizeof(buf), 0);
    t1 = GetTime();
    for (int i=0; i<count; ++i)
    {
        for (int j=2;j<(sizeof(buf)-4);j+=4)
        {
            tmp = *(int*)&buf[j];
            tmp++;
            *(int*)&buf[j] = tmp;
        }
    }
    t2 = GetTime();
    printf("use time : %ld\n", t2 - t1);
 
    tmp = 0;
    memset(buf, sizeof(buf), 0);
    t1 = GetTime();
    for (int i=0; i<count; ++i)
    {
        for (int j=3;j<(sizeof(buf)-4);j+=4)
        {
            tmp = *(int*)&buf[j];
            tmp++;
            *(int*)&buf[j] = tmp;
        }
    }
    t2 = GetTime();
    printf("use time : %ld\n", t2 - t1);
 
    tmp = 0;
    memset(buf, sizeof(buf), 0);
    t1 = GetTime();
    for (int i=0; i<count; ++i)
    {
        for (int j=0; j<(sizeof(buf)-4); j+=4)
        {
            tmp = *(int*)&buf[j];
            tmp++;
            *(int*)&buf[j] = tmp;
        }
    }
    t2 = GetTime();
    printf("use time : %ld\n", t2 - t1);

    return 0;
}
