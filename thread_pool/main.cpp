#include "threadpool.h"
#include <unistd.h>
#include <stdio.h>
#include <iostream>

using namespace std;


class TestJob: public CJob
{
public:
        int index;
        string name;
};

class EXJobWorker : public CJobWorker
{
public:
        void DoJob(CJob* job)
        {
                printf("job : %s-%d\n", ((TestJob*)job)->name.c_str(), ((TestJob*)job)->index);
                delete job;
                //usleep(1000*1000*7);
        }
};


int main()
{
#ifdef _KKK
    std::cout << "make effict" << std::endl;
    sleep(2);
#else 
    std::cout << "do not make effict" << std::endl;
    sleep(2);
#endif

        CUThreadPool pool(10);
        EXJobWorker *pt = new EXJobWorker;
        pool.Start(pt);

        for (int i =0; i < 1000; i++)
        {
                TestJob* job = new TestJob;
                job->index = i;
                job->name = "test";
                pool.ApendJob(job);
                usleep(1000*2);
        }

        while(1)
            sleep(1);

        delete pt;
        return 0;
}
