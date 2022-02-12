#include <iostream>
using namespace std;

template <typename T>
class Ptr {
public:
    Ptr(T* p): _p(p) {}
    explicit operator bool() const {
//    explicit operator int () const {
        if (_p != 0) 
            return true;
        else
            return false;
    }
private:
    T* _p;
};

int main() {
    int a;
    Ptr<int> p(&a);

    if (p)          // 自动转换为bool型，没有问题
        cout << "valid pointer." << endl;   // valid pointer.
    else
        cout << "invalid pointer." << endl;

    Ptr<double> pd(0);
    //cout << p + pd << endl; // 1, 相加，语义上没有意义
    cout << (p && pd) << endl; // 1, 相加，语义上没有意义
}


