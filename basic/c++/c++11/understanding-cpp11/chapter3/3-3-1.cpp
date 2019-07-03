#include <iostream>
using namespace std;

class HasPtrMem {
public:
    HasPtrMem(): d(new int(0)) {}
    ~HasPtrMem() { delete d; }
    int * d;
};

int main() {
    HasPtrMem a;
    HasPtrMem b(a);
    cout << *a.d << endl;   // 0
    cout << *b.d << endl;   // 0
}   // 析构：运行时错误，多次在同一位置调用delete
