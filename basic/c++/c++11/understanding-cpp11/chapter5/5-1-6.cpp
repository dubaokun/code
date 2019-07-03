#include <iostream>
using namespace std;

enum class C : char { C1 = 1, C2 = 2};
enum class D : unsigned int { D1 = 1, D2 = 2, Dbig = 0xFFFFFFF0U };

int main() {
    cout << sizeof(C::C1) << endl;   // 1

    cout << (unsigned int)D::Dbig << endl;   // 编译器输出一致,4294967280
    cout << sizeof(D::D1) << endl;     // 4
    cout << sizeof(D::Dbig) << endl;   // 4
    return 0;
}
