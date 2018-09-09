#include <pthread.h>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <stdio.h>

#include <sys/syscall.h>  
#define gettid() syscall(__NR_gettid)

using namespace std;

int main()
{
    cout<<"process id: "<<getpid()<<endl;
    cout<<"kernel id: "<<gettid()<<endl;
    //cout<<"std thread id: "<< std::this_thread::get_id()<<endl;
    cout<<"pthread id:"<< pthread_self()<<endl;
    return 0;
}
