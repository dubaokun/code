/*
 *Copyright (c) 2018 www.jd.com. All rights reserved.
 */

#pragma once

#include <thread>
#include <memory>
#include <queue>
#include <mutex>
#include <condition_variable>


class RebuildTaskScheduler {
 public:
    RebuildTaskScheduler();

    /**
     * @brief Start scheduler
     */
    void start();

 private:
    void runTasks();

 private:
    /**
     * @brief Backgroud Thread
     */
    std::unique_ptr<std::thread> thread_;

    /**
     * @brief Run one task at the same time
     */
    std::mutex rmutex_;

    /**
     * @brief Task queue mutex
     */
    std::mutex qmutex_;

    /**
     * @brief Conditional wait when task queue is empty
     */
    std::condition_variable empty_condition_;

    /**
     * @brief Conditional wait when task queue is non-empty
     */
    std::condition_variable nonempty_condition_;

    /**
     * @brief Task queue
     */
    //std::queue<std::shared_ptr<RebuildTask> > tasks_;

    /**
     * @brief Shutdown flag
     */
    volatile bool shutdown_;
};
