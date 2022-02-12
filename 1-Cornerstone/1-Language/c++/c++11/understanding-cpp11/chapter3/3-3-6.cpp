#include <iostream>
using namespace std;

class Moveable{
public:
    Moveable():i(new int(3)) {}
    ~Moveable() { delete i; }
    Moveable(const Moveable & m): i(new int(*m.i)) { }
    Moveable(Moveable && m):i(m.i) {
        m.i = nullptr; 
    }
    int* i;
};

int main() {
    Moveable a;

    Moveable c(move(a));    // 会调用移动构造函数
    cout << *a.i << endl;   // 运行时错误
}
