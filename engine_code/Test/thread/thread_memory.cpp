#include <time.h>
#include <unistd.h>  
#include <pthread.h>  
#include <deque>
#include <iostream>  
#include <string.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdlib.h>

using namespace std;  

__thread int var=10;					//两种方式效果一样  

void* worker1(void* arg);  
void* worker2(void* arg);  

char * get_memory()
{
	struct timeb timeSeed;
	ftime(&timeSeed);
	srand(timeSeed.millitm);
	int count = rand() % 8196;
	// get memory in heap
	char * pstr = new char[count + sizeof(char *)];
	for(int i = 0; i < count; ++i)
		pstr[i] = 'a';	
	char * pstr2 = new char[count / 2];
	for(int j = 0; j < count / 2; ++j)
		pstr2[j] = 'b';

	memcpy(pstr+count, &pstr2, sizeof(char *));  		

	// free memory
	delete [] *((char **)(pstr + count));
	delete [] pstr;
}

int main(int argc, char ** argv)
{  
    pthread_t pid1,pid2;  
    //__thread int temp=5;  
    static __thread  int temp=10;//修饰函数内的static变量  
    pthread_create(&pid1,NULL,worker1,NULL);  
    pthread_create(&pid2,NULL,worker2,NULL);  
    pthread_join(pid1,NULL);  
    pthread_join(pid2,NULL);  
    cout<<temp<<endl;//输出10  
	cout << "main" << --var << endl;
    return 0;  
}  
void* worker1(void* arg){  
	while(1)
		get_memory();
}  
void* worker2(void* arg){  
    sleep(1);//等待线程1改变var值，验证是否影响线程2  
    cout<<++var<<endl;//输出6  
}  
