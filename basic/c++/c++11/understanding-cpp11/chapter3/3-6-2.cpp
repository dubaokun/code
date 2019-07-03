#include <iostream>
using namespace std;

struct B1 {};
struct B2 {};

struct D1 : B1 {
    B1 b;       // 第一个非静态变量跟基类相同
    int i;
};

struct D2 : B1 {
    B2 b;
    int i;
};

int main() {
    D1 d1;
    D2 d2;
    cout << hex;
    cout << reinterpret_cast<long long>(&d1) << endl;       // 7ffffd945c60
    cout << reinterpret_cast<long long>(&(d1.b)) << endl;   // 7ffffd945c61
    cout << reinterpret_cast<long long>(&(d1.i)) << endl;   // 7ffffd945c64

    cout << reinterpret_cast<long long>(&d2) << endl;       // 7ffffd945c50
    cout << reinterpret_cast<long long>(&(d2.b)) << endl;   // 7ffffd945c50
    cout << reinterpret_cast<long long>(&(d2.i)) << endl;   // 7ffffd945c54

    cout << sizeof(d2.b) << endl;
    cout << sizeof(d1.b) << endl;
}
