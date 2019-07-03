#include <iostream>
using namespace std;

enum C { C1 = 1, C2 = 2};
enum D { D1 = 1, D2 = 2, Dbig = 0xFFFFFFF0U };
enum E { E1 = 1, E2 = 2, Ebig = 0xFFFFFFFFFLL};
int main() {
    cout << sizeof(C1) << endl;   // 4

    cout << Dbig << endl;   // 编译器输出不同,GCC：4294967280
    cout << sizeof(D1) << endl;     // 4
    cout << sizeof(Dbig) << endl;   // 4

    cout << Ebig << endl;   // 68719476735
    cout << sizeof(E1) << endl; // 8
    return 0;
}
