#include <type_traits>
#include <iostream>
using namespace std;

const int ic = 0;
volatile int iv;

struct S { int i; };

const S a = {0};
volatile S b;
volatile S* p = &b;

int main() {
    cout << is_const<decltype(ic)>::value << endl;      // 1
    cout << is_volatile<decltype(iv)>::value << endl;   // 1

    cout << is_const<decltype(a)>::value << endl;       // 1
    cout << is_volatile<decltype(b)>::value << endl;    // 1

    cout << is_const<decltype(a.i)>::value << endl;     // 0, 成员不是const
    cout << is_volatile<decltype(p->i)>::value << endl; // 0, 成员不是volatile
}
