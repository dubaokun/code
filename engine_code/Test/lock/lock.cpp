#include <unistd.h> 
 #include <pthread.h> 
 #include <string.h> 

 pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER; 
 pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER; 
 pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER; 
 pthread_mutex_t mutex4 = PTHREAD_MUTEX_INITIALIZER; 

 static int sequence1 = 0; 
 static int sequence2 = 0; 

 int func1() 
 { 
    pthread_mutex_lock(&mutex1); 
    ++sequence1; 
    sleep(1); 
    pthread_mutex_lock(&mutex2); 
    ++sequence2; 
    pthread_mutex_unlock(&mutex2); 
    pthread_mutex_unlock(&mutex1); 

    return sequence1; 
 } 

 int func2() 
 { 
    pthread_mutex_lock(&mutex2); 
    ++sequence2; 
    sleep(1); 
    pthread_mutex_lock(&mutex1); 
    ++sequence1; 
    pthread_mutex_unlock(&mutex1); 
    pthread_mutex_unlock(&mutex2); 

    return sequence2; 
 } 

 void* thread1(void* arg) 
 { 
    while (1) 
    { 
        int iRetValue = func1(); 

        if (iRetValue == 100000) 
        { 
            pthread_exit(NULL); 
        } 
    } 
 } 

 void* thread2(void* arg) 
 { 
    while (1) 
    { 
        int iRetValue = func2(); 

        if (iRetValue == 100000) 
        { 
            pthread_exit(NULL); 
        } 
    } 
 } 

 void* thread3(void* arg) 
 { 
    while (1) 
    { 
        sleep(1); 
        char szBuf[128]; 
        memset(szBuf, 0, sizeof(szBuf)); 
        strcpy(szBuf, "thread3"); 
    } 
 } 

 void* thread4(void* arg) 
 { 
    while (1) 
    { 
        sleep(1); 
        char szBuf[128]; 
        memset(szBuf, 0, sizeof(szBuf)); 
        strcpy(szBuf, "thread3"); 
    } 
 } 

 int main() 
 { 
    pthread_t tid[4]; 
    if (pthread_create(&tid[0], NULL, &thread1, NULL) != 0) 
    { 
        _exit(1); 
    } 
    if (pthread_create(&tid[1], NULL, &thread2, NULL) != 0) 
    { 
        _exit(1); 
    } 
    if (pthread_create(&tid[2], NULL, &thread3, NULL) != 0) 
    { 
        _exit(1); 
    } 
    if (pthread_create(&tid[3], NULL, &thread4, NULL) != 0) 
    { 
        _exit(1); 
    } 

    sleep(5); 
    //pthread_cancel(tid[0]); 

    pthread_join(tid[0], NULL); 
    pthread_join(tid[1], NULL); 
    pthread_join(tid[2], NULL); 
    pthread_join(tid[3], NULL); 

    pthread_mutex_destroy(&mutex1); 
    pthread_mutex_destroy(&mutex2); 
    pthread_mutex_destroy(&mutex3); 
    pthread_mutex_destroy(&mutex4); 

    return 0; 
 }