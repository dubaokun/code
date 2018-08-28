#include <thread>
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include "safe_queue.h"

void * run(void * argv)
{
    ThreadSafeQueue<int> * que_ = (ThreadSafeQueue<int> *)argv;
    while(1)
    {
        int a = 0;
        que_->Popup(a);
        std::cout << "a=" << a << std::endl;
    }
}

int main(int argc, char ** argv)
{
    ThreadSafeQueue<int> que_;

    // create thread by pthread_create
    //pthread_t ntid;
    //pthread_create(&ntid, NULL, run, (void *)&que_);

    // create thread by std::thread
    std::unique_ptr<std::thread> thread_;
    thread_.reset(new(std::nothrow)std::thread(run, (void *)&que_));
    if (NULL == thread_){
        std::cout << "Create Thread fail!" << std::endl;
        exit(0);
    }

    // mian loop to insert into queue
    for (int i = 0; ; ++i) {
        que_.Insert(i);
        sleep(1);
    }
    return 0;
}
