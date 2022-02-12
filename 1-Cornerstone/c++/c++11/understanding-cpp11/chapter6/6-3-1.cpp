#include <pthread.h>
#include <iostream>
using namespace std;

static long long total = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* func(void *) {
    long long i;
    for(i = 0; i < 100000000LL;i++) {   
        pthread_mutex_lock(&m);
        total += i;
        pthread_mutex_unlock(&m);
    }
}

int main() {
    pthread_t thread1, thread2;
    if (pthread_create(&thread1, NULL, &func, NULL)){
        throw;
    }
    if (pthread_create(&thread2, NULL, &func, NULL)){
        throw;
    }
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << total << endl;  // 9999999900000000
    return 0;
}
