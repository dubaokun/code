#include "profile_segment_lru_cache.h"
#include <iostream>
#include <map>
#include <pthread.h>
#include <string.h>

using namespace std;

#define BUFF_SIZE 4096
#define DOC_COUNT 1000000
#define THREAD_SIZE 10
#define CACHE_COUNT_PER_THREAD (DOC_COUNT / THREAD_SIZE)



profile::cache::ProfileSegmentLruCache * g_cache = NULL;
pthread_spinlock_t g_lock;
int g_get_ok = 0;
int g_get_error = 0;
map<int, int> g_map_ok;
map<int, int> g_map_error;

char * get_memory(int size) {
	char * pstr = new char[size];
	for (int i = 0; i < size; ++i)
		pstr[i] = 'a';
	
	return pstr;
}

void* worker1(void* arg){  
	for(int i = 0; i < DOC_COUNT; ++i) {
		char * pstr = get_memory(BUFF_SIZE);
		bool bRet = g_cache->simplePut(i, pstr);
		if (bRet) {
			//cout << "put docid " << i << " success!" << endl;
		} else {
			delete [] pstr;
			//cout << "put docid " << i << " failed!" << endl;
		}
	}

	for(int i = 0; i < DOC_COUNT; ++i) {
		char * pstr = NULL;
		bool bRet = g_cache->simpleGet(i, pstr);
		if (bRet) {
			//cout << "get docid " << i << " success! << len " << strlen(pstr) << endl;
			pthread_spin_lock(&g_lock);
			g_map_ok[i] = 0;
			pthread_spin_unlock(&g_lock);
		} else {
			//cout << "get docid " << i << " failed!" << endl;
			pthread_spin_lock(&g_lock);
			g_map_error[i] = 0;
			pthread_spin_unlock(&g_lock);

		}
	}
	pthread_spin_lock(&g_lock);
	cout << "ok=" << g_map_ok.size() << " error" << g_map_error.size() << endl;
	pthread_spin_unlock(&g_lock);


	while(1)
		sleep(1);
}  
void* worker2(void* arg){  
	for(int i = 0; i < CACHE_COUNT_PER_THREAD / 2; ++i) {
		char * pstr = NULL;
		bool bRet = g_cache->simpleGet(i, pstr);
		if (bRet) {
			//cout << "get docid " << i << " success! << len " << strlen(pstr) << endl;
		} else {
			//cout << "get docid " << i << " failed!" << endl;
		}
	}
	
	while(1)
		sleep(1);
	
}

int main(int argc, char ** argv)
{  
	g_cache = new profile::cache::ProfileSegmentLruCache(DOC_COUNT, THREAD_SIZE, CACHE_COUNT_PER_THREAD, 10);
	pthread_spin_init(&g_lock, PTHREAD_PROCESS_PRIVATE);
	if (NULL == g_cache) {
		cout << "new cache fail" << endl;
		return -1;
	}

	for (int i = 0; i < 10; ++i) {
    	pthread_t pid1;  
    	if ( 0 != (pthread_create(&pid1,NULL,worker1,NULL)))
		{
			cout << "create thread error!" << endl;
			return -2;
		}  
		
	}
	
	while(1)
		sleep(1);
	
	for (int i = 0; i < 10; ++i) {
    	pthread_t pid1;  
    	if ( 0 != (pthread_create(&pid1,NULL,worker2,NULL)))
		{
			cout << "create thread error!" << endl;
			return -2;
		}  
		
	}
	

	while(1) {
		sleep(1);
	}

    return 0;  
}
