#include <iostream>
#include <atomic>
using namespace std;

atomic<int*> p1;
atomic<int*> p2;
atomic<int*> p3;
atomic<int*> p4;

void func_in1(int* val) {
    cout << *val << endl;
}

void func_in2(int* [[carries_dependency]] val) {
    p2.store(val, memory_order_release);
    cout << *p2 << endl;
}

[[carries_dependency]] int* func_out() {
    return (int *)p3.load(memory_order_consume);
}

void Thread() {
    int* p_ptr1 = (int *)p1.load(memory_order_consume);     // L1
    cout << *p_ptr1 << endl;// L2

    func_in1(p_ptr1);       // L3
    func_in2(p_ptr1);       // L4
        
    int * p_ptr2 = func_out();  // L5
    p4.store(p_ptr2, memory_order_release); // L6
    cout << *p_ptr2 << endl; 
}
