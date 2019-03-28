//g++ -O2 -std=c++11 -pthread thread_test.cpp
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <thread>

using namespace std;

volatile bool stop = false;

char *buff = nullptr;
int Write(int offset) {
    printf("write offset:%d\n", offset);
    while (true) {
        int64_t num = rand()%1000000000;
        num*=11111;
        //printf("write num:%ld\n", num);

        int64_t *ptr = (int64_t*)(buff+offset);

        //*ptr = num;
        __sync_lock_test_and_set(ptr, num);
        //memcpy(buff+offset, &num, 8);
        if (stop) break;
    }
    return 0;
}

int Read(int offset) {
    printf("read offset:%d\n", offset);
    while (true) {
        int64_t num = 0;
        num = *(int64_t *)(buff+offset);
    
        //memcpy(&num, buff+offset, 8);
        //printf("num:%ld\n", num);
        if ((num % 11111) != 0) {
            printf("num %ld offset:%d\n", num, offset);
            break;
        }

        if (stop) break;
    }
    return 0;
}
int main() {
    int len = 1<<30;
    buff = new char[len];
    memset(buff, 0, len);
    thread **t1 = new thread*[12]; 
    //for (int i=0; i<10; ++i) {
    //    thread *t1 = new thread(Write, 8*i+3); 
    //}
    //int offset = 43;
    int offset = 3;
    while (1) {
        //memset(buff+offset, 0, 32);
        stop = false;
        printf("offset:%d count:%d\n", offset, (offset-3)%16);
        t1[0] = new thread(Write, offset); 
        t1[1] = new thread(Write, 8+offset); 

        for (int i=0; i<5; ++i) {
            t1[i+2] = new thread(Read, offset); 
        }

        for (int i=0; i<5; ++i) {
            t1[i+7] = new thread(Read, 8+offset); 
        }
        sleep(10);

        stop = true;
        for (int i=0; i<12; ++i) {
            t1[i]->join();
            delete t1[i];
        }
        offset += 16;
        sleep(3);
    }
 

}
