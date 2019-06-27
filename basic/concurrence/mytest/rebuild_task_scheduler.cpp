/*
 *Copyright (c) 2018 www.jd.com. All rights reserved.
 */

#include "rebuild_task_scheduler.h"
#include <unistd.h>
#include <iostream>


RebuildTaskScheduler::RebuildTaskScheduler() : shutdown_(false) {}

void Run1() {
    while(1) {
        std::cout << "Run1 " << std::endl;
        sleep(1);
    }
}

void Run2(int i) {
    while(1) {
        std::cout << "Run1 " << i << std::endl;
        sleep(1);
    }
}


void RebuildTaskScheduler::start() {
    if (!shutdown_ && NULL == thread_.get()) {
		//thread_.reset(new std::thread(std::bind(&RebuildTaskScheduler::runTasks, this)));
        thread_.reset(new std::thread(&RebuildTaskScheduler::runTasks, this));
        //thread_.reset(new std::thread(Run1));
        //thread_.reset(new std::thread(Run2, 2));
    }
}


void RebuildTaskScheduler::runTasks() {
    while (!shutdown_) {
        std::cout << "Thread Run!" << std::endl;
        sleep(1);
    }
    /*
        boost::shared_ptr<RebuildTask> task;
        {
            std::unique_lock<std::mutex> ul(qmutex_);
            while (true) {
                if (shutdown_) return;
                if (!tasks_.empty()) {
                    break;
                }
                empty_condition_.wait(ul);
            }
            task = tasks_.front();
            assert(NULL != task.get());
            tasks_.pop();
            if (tasks_.empty()) nonempty_condition_.notify_one();
        }

        {
            std::unique_lock<std::mutex> ul(rmutex_);
            if (!shutdown_) {
                task->run();
            }
        } 
    }*/ 
}

int main(int argc, char ** argv) {
    RebuildTaskScheduler scheduler;
    scheduler.start();
    while(1) {
        sleep(1);
    }
}
