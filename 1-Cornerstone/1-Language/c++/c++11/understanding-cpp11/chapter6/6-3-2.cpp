#include <atomic>
#include <thread>
#include <iostream>
using namespace std;

atomic_llong total {0};     // 原子数据类型
 
void func(int) {
    for(long long i = 0; i < 100000000LL; ++i) {
        total += i;
    }
}

int main() {
    thread t1(func, 0);
    thread t2(func, 0);
    
    t1.join();
    t2.join();
    cout << total << endl;  // 9999999900000000
    return 0;
}
