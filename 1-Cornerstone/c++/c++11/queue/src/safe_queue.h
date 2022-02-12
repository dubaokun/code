#ifndef __SAFE_QUEUE_H__
#define __SAFE_QUEUE_H__

#include <mutex>
#include <queue>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
    public:
        ThreadSafeQueue();
        ~ThreadSafeQueue();

    public:
	    void Insert(T value);
	    void Popup(T &value);
        bool Empty();

    private:
	    std::mutex mut_;
	    std::condition_variable cond_;
	    std::queue<T> que_;
};

template <typename T>
ThreadSafeQueue<T>::ThreadSafeQueue()
{
}

template <typename T>
ThreadSafeQueue<T>::~ThreadSafeQueue()
{
}

template <typename T>
void ThreadSafeQueue<T>::Insert(T value)
{
	std::lock_guard<std::mutex> lk(mut_);
	que_.emplace(value);
	cond_.notify_one();
}

template <typename T>
void ThreadSafeQueue<T>::Popup(T &value)
{
	std::unique_lock<std::mutex> lk(mut_);
	cond_.wait(lk, [this]{return !que_.empty();});
	value = que_.front();
	que_.pop();
}

template <typename T>
bool ThreadSafeQueue<T>::Empty()
{
        std::lock_guard<std::mutex> lk(mut_);
        return que_.empty();
}


#endif
