#include <thread>
#include <atomic>
#include <iostream>
#include <unistd.h>
using namespace std;
 
std::atomic_flag lock = ATOMIC_FLAG_INIT;
 
void f(int n) {
    while (lock.test_and_set(std::memory_order_acquire))    // 尝试获得锁
        cout << "Waiting from thread " << n << endl;        // 自旋
    cout << "Thread " << n << " starts working" << endl;
}
 
void g(int n) {
    cout << "Thread " << n << " is going to start." << endl;
    lock.clear(); 
    cout << "Thread " << n << " starts working" << endl;
}

int main() {
    lock.test_and_set();
    thread t1(f, 1);
    thread t2(g, 2); 

    t1.join();
    usleep(100);
    t2.join();
}
