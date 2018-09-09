#include <iostream>  
#include <pthread.h>  
#include <unistd.h>  

using namespace std;  

const int i=5;  
__thread int var=i;//两种方式效果一样  

int g_count = 0;
pthread_spinlock_t g_lock;

void* worker1(void* arg);  
void* worker2(void* arg);  

int main(){  
	pthread_spin_init(&g_lock, PTHREAD_PROCESS_PRIVATE);
    pthread_t pid1,pid2;  
    pthread_create(&pid1,NULL,worker1,NULL);  
    pthread_create(&pid2,NULL,worker2,NULL);  
    pthread_join(pid1,NULL);  
    pthread_join(pid2,NULL);  

	cout << "main" << g_count << endl;
    return 0;  
}  
void* worker1(void* arg){  
	for (int i=0; i<10000; ++i) {
		pthread_spin_lock(&g_lock);
		g_count ++;
		pthread_spin_unlock(&g_lock);
	}
}  
void* worker2(void* arg){  
	for (int i=0; i<10000; ++i) {
		pthread_spin_lock(&g_lock);
		g_count-- ;
		pthread_spin_unlock(&g_lock);
	}

}  
