#include <thread>
#include <atomic>
#include <iostream>
using namespace std;

atomic<int> a;
atomic<int> b;

int Thread1(int) {
    int t = 1;
    a.store(t, memory_order_relaxed);
    b.store(2, memory_order_release);   // 本原子操作前所有的写原子操作必须完成
}

int Thread2(int) {
    while(b.load(memory_order_acquire) != 2);  // 本原子操作必须完成才能执行之后所有的读原子操作
    cout << a.load(memory_order_relaxed) << endl;   // 1
}

int main() {
    thread t1(Thread1, 0);
    thread t2(Thread2, 0);

    t1.join();
    t2.join();
    return 0;
}
