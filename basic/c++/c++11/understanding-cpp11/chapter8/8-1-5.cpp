#include <iostream>
using namespace std;

void f() alignas(double); // 错误：alignas不能修饰函数
 alignas(double) unsigned char c[sizeof(double)]; // 正确
extern unsigned char c[sizeof(double)]; 
extern unsigned char c[sizeof(double)] alignas(float); // 不同的对齐定义

int main(){
    cout << alignof(c) << endl;
//    cout << alignof(f) << endl;
}

