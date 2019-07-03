#include <iostream>
using namespace std;

int main() {
    unsigned int a = 4294967295;    //最大的unsigned int值
    unsigned int b = 1;
    auto c = a + b;         // c的类型依然是unsigned int

    cout << "a = " << a << endl;    // a = 4294967295
    cout << "b = " << b << endl;    // b = 1
    cout << "a + b = " << c << endl;// a + b = 0
    return 0;
}

