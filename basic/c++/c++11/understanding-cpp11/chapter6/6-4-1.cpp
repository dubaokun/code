#include <pthread.h>
#include <iostream>
using namespace std;

__thread int errorCode = 0;

void* MaySetErr(void * input) {
    if (*(int*)input == 1)
        errorCode = 1;
    else if (*(int*)input == 2)
        errorCode = -1;
    else
        errorCode = 0;
}

int main() {
    int input_a = 1;
    int input_b = 2;

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, &MaySetErr, &input_a);
    pthread_create(&thread2, NULL, &MaySetErr, &input_b);

    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);
    cout << errorCode << endl;  
}
